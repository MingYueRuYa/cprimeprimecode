#ifndef app_h
#define app_h

#include "iocpserver.h"
#include "message.hpp"

class App
{
public:
    App();
    ~App();

    void Run(const char *ip, unsigned short port, unsigned int nListen = 5);

    void onClientConnected(const Connection *conn);
    void OnClientDisconnected(const Connection *conn);
    void OnRead(const Connection *con , void *data, std::size_t size);
    void OnWrite(const Connection *conn, std::size_t bytes_transferred);
    void ProcessMessage(MessageHeader *msgHeader, Connection *conn);

private:
    IocpServer _iocpServer;

};


#endif // app_h