#ifndef _callback_h
#define _callback_h

#include "connection.h"
#include <functional>

namespace Callback
{
    typedef std::function<void (const Connection *, std::size_t)> OnWrite;
    typedef std::function<void (const Connection *, void *, std::size_t)> OnRead;
    typedef std::function<void (const Connection *)> OnConnected;
    typedef std::function<void (const Connection *)> OnDisconnected;
}

class CallbacksExecutor
{
public:
    CallbacksExecutor();
    virtual ~CallbacksExecutor() {}

public:
    void SetOnWriteCallback(Callback::OnWrite callback);
    void SetOnReadCallback(Callback::OnRead callback);
    void SetOnConnectedCallback(Callback::OnDisconnected callback);
    void SetOnDisconnectedCallback(Callback::OnConnected callback);

public:
    Callback::OnWrite OnWrite;
    Callback::OnRead  OnRead;
    Callback::OnConnected OnConnected;
    Callback::OnDisconnected OnDisconnected;

};


#endif // _callback_h