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
#ifdef _WIN32
    #define EAGAIN WSAEWOULDBLOCK
    #define EINTR WSAEINTR
    #include <WinSock2.h> // struct sockaddr_in
    #include <WS2tcpip.h>
    #pragma comment(lib,"WS2_32.lib")
#else
    #include <arpa/inet.h> // struct sockaddr_in
    #include <netdb.h> // addrinfo
    #include <sys/socket.h>
    #include <unistd.h>
    #include <sys/select.h>
    #include <sys/ioctl.h>
    #include <sys/time.h>
#endif // !_WIN32

// android log
#ifdef ANDROID
#define printf(...)  __android_log_print(ANDROID_LOG_DEBUG, "AsyncTCP",__VA_ARGS__)
#endif

#include "cocos/network/AsyncTCP.h"
#include "base/CCScheduler.h"
#include "base/CCDirector.h"

static int getErrno(void)
{
#ifdef _WIN32
    return (int)WSAGetLastError();
#else
    return errno;
#endif
}

static void printErrno(const char *prefix)
{
    int err = getErrno();
#ifdef _WIN32
    char utf8[128] = {0};
    LPTSTR lpMessageBuf;
    int nLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, err, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), (LPTSTR)&lpMessageBuf,
        0, NULL);
    WideCharToMultiByte(CP_UTF8, 0, lpMessageBuf, nLen, utf8, sizeof(utf8), NULL, NULL);
    LocalFree(lpMessageBuf);
    printf("==%s error with errno: %d, %s\n", prefix, err, utf8);
#else
    printf("==%s error with errno: %d, %s\n", prefix, err, strerror(err));
#endif
}

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
,_timeout(0)
,_cb(nullptr)
,_quit(false)
,_thread(nullptr)
,_sendData(nullptr)
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

void AsyncTCP::open(const std::string host, int port, int timeout)
{
    // lua must call close() first, wait CLOSED event, then can open again.
    waitThreadAndClean();
    
    _quit = false;
    _host = host;
    _port = port;
    _timeout = timeout;
    _thread = new std::thread(&AsyncTCP::socketThread, this);
}

void AsyncTCP::send(unsigned char *buffer, size_t len)
{
    if (_tcp < 0) {
        printf("==send Error, AsyncTCP NOT opened\n");
        return;
    }
    
    _sendMutex.lock();
    if (_sendData) {
        // merge package
        _sendData->buffer = (unsigned char *)realloc(_sendData->buffer, _sendData->size + len);
        memcpy(_sendData->buffer + _sendData->size, buffer, len);
        _sendData->size += len;
    } else {
        _sendData = new TCPData(0, buffer, len);
    }
    _sendMutex.unlock();
}

void AsyncTCP::close()
{
    _quit = true;// make socketThread exit
}

void AsyncTCP::notify(int state, unsigned char *msg, size_t size)
{
    bool needNew = true;
    _getMutex.lock();
    if (EVENT_DATA == state && !_getQueue.empty()) {
        // merge data if last package is data
        TCPData *data = _getQueue.back();
        if (EVENT_DATA == data->state) {
            data->buffer = (unsigned char *)realloc(data->buffer, data->size + size);
            memcpy(data->buffer + data->size, msg, size);
            data->size += size;
            needNew = false;
        }
    }
    if (needNew) {
        TCPData *data = new TCPData(state, msg, size);
        _getQueue.push(data);
    }
    _getMutex.unlock();
}

void AsyncTCP::waitThreadAndClean()
{
    if (_thread) {
        _thread->join();
        delete _thread;
    }
    // clean cache
    if (_sendData) {
        delete _sendData;
        _sendData = nullptr;
    }
    while (!_getQueue.empty()) {
        TCPData *data = _getQueue.front();
        _getQueue.pop();
        delete data;
    }
}

void AsyncTCP::update(float dt)
{
    while (true) {
        // get data from queue
        TCPData *data = nullptr;
        _getMutex.lock();
        if (!_getQueue.empty()) {
            data = _getQueue.front();
            _getQueue.pop();
        }
        _getMutex.unlock();
        // not data, break
        if (!data) break;
        // notify lua
        _cb(data->state, data->buffer, data->size);
        // free data
        delete data;
        // if last _cb call close(), exit loop
        if (_quit) break;
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
        
        int rtn = 0;
        _sendMutex.lock();
        if (_sendData) {
            rtn = sendTCP(_sendData->buffer, _sendData->size);
            // free data
            delete _sendData;
            _sendData = nullptr;
        }
        _sendMutex.unlock();
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
        int err = getErrno();
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
        int err = getErrno();
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
        printErrno("socket");
        return -2;
    }

    // set non-blocking.
    unsigned long noBlock = 1UL;
#ifdef _WIN32
    ret = ioctlsocket(_tcp, FIONBIO, &noBlock);
    if (ret == SOCKET_ERROR) {
        printErrno("ioctlsocket");
        return -3;
    }
#else
    ret = ioctl(_tcp, FIONBIO, &noBlock);
    if (ret == -1) {
        printErrno("ioctl");
        return -3;
    }
#endif //!WIN32
    
    // connect with non-blocking
    if (isIpv6) {
        struct sockaddr_in6 servaddr6;
        memset(&servaddr6, 0, sizeof(servaddr6));
        servaddr6.sin6_family = AF_INET6;
        servaddr6.sin6_port = htons(_port);
        ret = inet_pton(AF_INET6, _host.c_str(), &servaddr6.sin6_addr);
        if (ret <= 0) {
            printErrno("inet_pton AF_INET6");
            return -1;
        }
        connect(_tcp, (const struct sockaddr*)(&servaddr6), sizeof(servaddr6));// not check ret when non-blocking
    } else {
        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(_port);
        ret = inet_pton(AF_INET, _host.c_str(), &servaddr.sin_addr);
        if (ret <= 0) {
            printErrno("inet_pton AF_INET");
            return -1;
        }
        connect(_tcp, (const struct sockaddr*)(&servaddr), sizeof(servaddr));// not check ret when non-blocking
    }
	
    // check can write with timeout
    struct timeval tv;
    tv.tv_sec = _timeout;
    tv.tv_usec = 0;

    fd_set fdwrite;
    FD_ZERO(&fdwrite);
    FD_SET(_tcp, &fdwrite);

    ret = select((int)_tcp + 1, NULL, &fdwrite, NULL, &tv);
    if (ret > 0 && FD_ISSET(_tcp, &fdwrite)) {
        int error = -1;
        int optLen = sizeof(int);
        getsockopt(_tcp, SOL_SOCKET, SO_ERROR, (char *)&error, (socklen_t *)&optLen);
        if (0 == error) {
            return 0; // connect socket successful.
        }
        printErrno("getsockopt");
    } else {
        printErrno("select timeout");
    }
    return -1;
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
