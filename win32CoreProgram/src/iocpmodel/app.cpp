#include "app.h"

App::App()
{
    _iocpServer.SetOnConnectedCallback(std::bind(&App::onClientConnected, this,
                                        std::placeholders::_1));
    _iocpServer.SetOnDisconnectedCallback(std::bind(&App::OnClientDisconnected,
                                        this, std::placeholders::_1));
    _iocpServer.SetOnReadCallback(std::bind(&App::OnRead, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    _iocpServer.SetOnWriteCallback(std::bind(&App::OnWrite,
            this,std::placeholders::_1, std::placeholders::_2));
}

App::~App()
{
}

void App::onClientConnected(const Connection *conn)
{
    fprintf(stderr, "新客户端链接\n");
    _iocpServer.AsyncRead(conn);
}

void App::OnClientDisconnected(const Connection *conn)
{
    auto variable_conn = const_cast<Connection *>(conn);
    SOCKET clifd = variable_conn->GetSocket();
    fprintf(stderr, "client:%d 断开\n", clifd);
}

void App::OnRead(const Connection *con , void *data, std::size_t size)
{
    char *value = reinterpret_cast<char *>(data);
    //我们不应该这么写，可能会超出ReadBuffer的长度
	//value[size] = '\0';
    
    // 不解除const限定符，GetSocket()就不能调用，因为它的返回值是个引用
    auto variable_conn = const_cast<Connection *>(con);

    SOCKET clifd = variable_conn->GetSocket();
    fprintf(stderr, "client:%d, msg:%s\n", clifd, value);

    //ECHO功能，给客户端发送回去
    _iocpServer.AsyncWrite(con, value, size);
}

void App::OnWrite(const Connection *conn, std::size_t bytes_transferred)
{
    // 继续异步读取客户端
    _iocpServer.AsyncRead(conn);
}

void App::Run(const char *ip, unsigned short port, unsigned int nListen)
{
    _iocpServer.Run(ip, port, nListen);
}
