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

#ifndef __ASYNC_TCP_H__
#define __ASYNC_TCP_H__

#include <functional>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <memory.h>

#include "base/CCRef.h"

class AsyncTCP : public cocos2d::Ref
{
public:
    static void initEnv();
    AsyncTCP();
    ~AsyncTCP();
    
    // state: 1 connecting, 2 failed, 3 connected, 4 data, 5 closed.
    void setEventCB(std::function<void(int state, unsigned char *msg, size_t size)> cb);
    void open(const std::string host, int port, int timeout = 10);
    void send(unsigned char *buffer, size_t len);
    void close();
    
private:
    enum {
        EVENT_CONNECTING,
        EVENT_FAILED,
        EVENT_CONNECTED,
        EVENT_CLOSED,
        EVENT_DATA
    };
    
    struct TCPData {
    public:
        TCPData(int stat, unsigned char *b, size_t s)
        : buffer(nullptr)
        , size(s)
        , state(stat)
        {
            buffer = (unsigned char *)malloc(s);
            memcpy(buffer, b, s);
        }
        ~TCPData()
        {
            if (buffer) free(buffer);
        };
        unsigned char *buffer;
        size_t size;
        int state;
    };
    
    void update(float dt);
    void waitThreadAndClean();
    
    void socketThread();
    void notify(int state, unsigned char *msg, size_t size); // call on socketThread
    int openTCP(bool isIpv6); // call on socketThread
    void closeTCP(); // call on socketThread
    int recvTCP(); // call on socketThread
    int sendTCP(unsigned char *buff, size_t size); // call on socketThread
    
    int _tcp;
    std::string _host;
    int _port;
    int _timeout;
    std::function<void(int state, unsigned char *msg, size_t size)> _cb;
    bool _quit;
    
    std::thread *_thread;
    TCPData * _sendData; // send to server
    std::mutex _sendMutex;
    std::queue<TCPData *> _getQueue; // get from server
    std::mutex _getMutex;
};

#endif // __ASYNC_TCP_H__
