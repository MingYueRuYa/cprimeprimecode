/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef tcpserver_h
#define tcpserver_h

//避免早期定义的一些宏
#define WIN32_LEAN_AND_MEAN

#include "connection.h"
#include "callbacks.h"
#include "chronotimer.hpp"

#include <Windows.h>
#include <MSWSock.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <cstdio>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>

using std::thread;
using std::mutex;
using std::cout;
using std::endl;
using std::vector;

#pragma comment(lib, "ws2_32.lib")

const int kBUFFSIZE = 1024;

class IocpServer : public CallbacksExecutor
{
public:
    IocpServer();
    ~IocpServer();

    int Init(const char *ip, unsigned short port, unsigned int nListen);
    int WinSockInit();
    int InitSocket();
    int Accept();
    int Bind(const char *ip, unsigned short port);
    int Listen(unsigned int nListen);
    void Run(const char *ip, unsigned short port, unsigned int nListen);
    void Mainloop();
    void AsyncRead(const Connection *conn);
    void AsyncWrite(const Connection *conn, void *data, std::size_t size);

public:
    bool _wsa_inited;
    HANDLE _completion_port;
    SOCKET _socket;
    vector<Connection *> mConnectionVec;
    mutex mMutex;
    ChronoTimer _chrono_timer;
    int _client_count;
    std::atomic_int  _msg_count;
    LPFN_ACCEPTEX _acceptex_func;

};


#endif // tcpserver_h
