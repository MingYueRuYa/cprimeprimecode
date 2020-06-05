#ifndef worker_h
#define worker_h

#include "iocpserver.h"

#include <MSWSock.h>

class Workers
{
public:
    Workers(IocpServer *server);
    void Start();
    void ThreadProc();

private:
    IocpServer *_iocpServer;

};


#endif // worker_h