// Copyright 2020 KeNan Liu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdint.h>
#include <functional>
#include <sys/types.h>
#include <fcntl.h>
#ifdef _WIN32
    #include <WinSock2.h> // struct sockaddr_in
    #include <WS2tcpip.h>
    #pragma comment(lib,"WS2_32.lib")
#else
    #include <arpa/inet.h> // struct sockaddr_in
    #include <netdb.h> // addrinfo
    #include <sys/socket.h>
    #include <unistd.h>
#endif // !_WIN32

#include "cocos/network/AsyncTCP.h"
#include "base/CCScheduler.h"
#include "base/CCDirector.h"

static int checkIPv6(const char *hostname, bool &isIpv6)
{
    struct addrinfo *iterator = NULL, *resolved = NULL;
    struct addrinfo hints;
    int ret = 0;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = PF_UNSPEC;
    
    ret = getaddrinfo(hostname, NULL, &hints, &resolved);
    if (ret != 0) {
        printf("== AsyncTCP getaddrinfo error:%d\n", ret);
        return ret;
    }

    isIpv6 = false;
    for (iterator = resolved; iterator; iterator = iterator->ai_next) {
        char hbuf[NI_MAXHOST];
        ret = getnameinfo(iterator->ai_addr, (socklen_t) iterator->ai_addrlen,
                hbuf, (socklen_t) sizeof(hbuf), NULL, 0, NI_NUMERICHOST);
        if (ret) {
            freeaddrinfo(resolved);
            printf("== AsyncTCP getnameinfo error:%d\n", ret);
            return ret;
        }
        if (iterator->ai_family == AF_INET6) {
            isIpv6 = true;
            break;
        }
    }
    freeaddrinfo(resolved);
    return 0;
}

void AsyncTCP::initEnv()
{
#ifdef _WIN32
    WSADATA wsaData;
    auto ver = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (ver) {
        printf("WSAStartup failed !\n");
    }
#else
    signal(SIGPIPE, SIG_IGN);// avoid crash when socket is closed
#endif
}

AsyncTCP::AsyncTCP()
:_tcp(-1)
,_host("")
,_port(0)
,_cb(nullptr)
,_quit(false)
,_thread(nullptr)
{
    cocos2d::Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(AsyncTCP::update), this, 0, false);
}

AsyncTCP::~AsyncTCP()
{
    close();
    waitThreadAndClean();
    cocos2d::Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(AsyncTCP::update), this);
}

void AsyncTCP::setEventCB(std::function<void(int state, unsigned char *msg, size_t size)> cb)
{
    _cb = cb;
}

void AsyncTCP::open(const std::string host, int port)
{
    // lua must call close() first, wait CLOSED event, then can open again.
    waitThreadAndClean();
    
    _quit = false;
    _host = host;
    _port = port;
    _thread = new std::thread(&AsyncTCP::socketThread, this);
}

void AsyncTCP::send(unsigned char *buffer, size_t len)
{
    if (_tcp < 0) {
        printf("==send Error, AsyncTCP NOT opened\n");
        return;
    }
    
    TCPData *data = new TCPData(0, buffer, len);
    sendMutex.lock();
    sendQueue.push(data);
    sendMutex.unlock();
}

void AsyncTCP::close()
{
    _quit = true;// make socketThread exit
}

void AsyncTCP::notify(int state, unsigned char *msg, size_t size)
{
    TCPData *data = new TCPData(state, msg, size);
    getMutex.lock();
    getQueue.push(data);
    getMutex.unlock();
}

void AsyncTCP::waitThreadAndClean()
{
    if (_thread) {
        _thread->join();
        delete _thread;
    }
    // clean cache
    while (!sendQueue.empty()) {
        TCPData *data = sendQueue.front();
        sendQueue.pop();
        delete data;
    }
    while (!getQueue.empty()) {
        TCPData *data = getQueue.front();
        getQueue.pop();
        delete data;
    }
}

void AsyncTCP::update(float dt)
{
    while (true) {
        // get data from queue
        TCPData *data = nullptr;
        getMutex.lock();
        if (!getQueue.empty()) {
            data = getQueue.front();
            getQueue.pop();
        }
        getMutex.unlock();
        // not data, break
        if (!data) break;
        // notify lua
        _cb(data->state, data->buffer, data->size);
        // free data
        delete data;
    }
}

void AsyncTCP::socketThread()
{
    // 1. check dns isIpv6
    notify(EVENT_CONNECTING, nullptr, 0);
    bool isIpv6;
    if (checkIPv6(_host.c_str(), isIpv6)) {
        notify(EVENT_FAILED, nullptr, 0);
        return; // get error in checkIPv6
    }
    
    // 2. open socket
    if (openTCP(isIpv6) < 0) {
        closeTCP();
        notify(EVENT_FAILED, nullptr, 0);
        return; // open error
    }
    notify(EVENT_CONNECTED, nullptr, 0);
    
    // 3. TCP loop
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));// 1 ms
        if (_quit) break;
        
        if (recvTCP() < 0) break;
        
        int rtn;
        while (true) {
            // get data from queue
            TCPData *data = nullptr;
            rtn = 0;
            sendMutex.lock();
            if (!sendQueue.empty()) {
                data = sendQueue.front();
                sendQueue.pop();
            }
            sendMutex.unlock();
            // not data, break
            if (!data) break;
            // send data
            rtn = sendTCP(data->buffer, data->size);
            // free data
            delete data;
            // closed
            if (rtn < 0) break;
        }
        if (rtn < 0) break; // closed
    }
    
    // 4. close
    closeTCP();
    notify(EVENT_CLOSED, nullptr, 0);
}

int AsyncTCP::recvTCP()
{
    unsigned char rbuf[1024] = {0};
    while (true) {
        int ret = recv(_tcp, (char *)rbuf, sizeof(rbuf), 0);
        int err = errno;
        if (ret > 0) {
            notify(EVENT_DATA, rbuf, ret);
            continue;
        }
        if (ret == 0) {
            return -1; // closed
        }
        
        if (err == EINTR) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));// 1 ms
            continue; // Interrupted
        }
        if (err == EAGAIN) {
            break; // block, no more data
        }
        // other error
        return -1; // closed
    }
    return 0;
}

int AsyncTCP::sendTCP(unsigned char *buff, size_t size)
{
    size_t offset = 0;
    while (true) {
        int ret = ::send(_tcp, (const char *)(buff + offset), size, 0);
        int err = errno;
        if (ret >= 0) {
            size -= ret;
            if (size == 0) break; // all sended
            offset += ret;
            continue;
        }
        // Interrupted or block
        if (err == EINTR || err == EAGAIN) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));// 1 ms
            continue;
        }
        // other error
        return -1;
    }
    return 0;
}

int AsyncTCP::openTCP(bool isIpv6)
{
    int ret;
    
    if (isIpv6) {
        _tcp = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    } else {
        _tcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    if (_tcp < 0) {
        printf("==socket error with errno: %d, %s\n", errno, strerror(errno));
        return -2;
    }
    
    if (isIpv6) {
        struct sockaddr_in6 servaddr6;
        memset(&servaddr6, 0, sizeof(servaddr6));
        servaddr6.sin6_family = AF_INET6;
        servaddr6.sin6_port = htons(_port);
        ret = inet_pton(AF_INET6, _host.c_str(), &servaddr6.sin6_addr);
        if (ret <= 0) {
            printf("==inet_pton AF_INET6 ret %d, errno %d, %s\n", ret, errno, strerror(errno));
            return -1;
        }
        ret = connect(_tcp, (const struct sockaddr*)(&servaddr6), sizeof(servaddr6));
        if (ret < 0) {
            printf("==connect6 error with errno: %d, %s\n", errno, strerror(errno));
            return -1;
        }
    } else {
        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(_port);
        ret = inet_pton(AF_INET, _host.c_str(), &servaddr.sin_addr);
        if (ret <= 0) {
            printf("==inet_pton AF_INET ret %d, errno %d, %s\n", ret, errno, strerror(errno));
            return -1;
        }
        ret = connect(_tcp, (const struct sockaddr*)(&servaddr), sizeof(servaddr));
        if (ret < 0) {
            printf("==connect error with errno: %d, %s\n", errno, strerror(errno));
            return -1;
        }
    }
    
    // set non-blocking after connected.
#ifdef _WIN32
    unsigned long NoBlock = 1UL;
    int nRes = ioctlsocket(_tcp, FIONBIO, &NoBlock);
    if (nRes == SOCKET_ERROR) {
        printf("==ioctlsocket error with errno: %d, %s\n", errno, strerror(errno));
        return -3;
    }
#else
    int flags = fcntl(_tcp, F_GETFL, 0);
    if (flags == -1) {
        printf("==socket non-blocking get fcntl error with errno: %d, %s\n", errno, strerror(errno));
        return -3;
    }
    ret = fcntl(_tcp, F_SETFL, flags | O_NONBLOCK);
    if (ret == -1) {
        printf("==socket non-blocking set fcntl error with errno: %d, %s\n", errno, strerror(errno));
        return -3;
    }
#endif //!WIN32
    
    return 0;
}

void AsyncTCP::closeTCP()
{
    if (_tcp > 0) {
#if _WIN32
        closesocket(_tcp);
#else
        ::close(_tcp);
#endif
        _tcp = -1;
    }
}
