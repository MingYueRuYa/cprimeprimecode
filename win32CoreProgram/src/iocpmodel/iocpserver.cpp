#include "iocpserver.h"
#include "overlapped.h"
#include "socketexfunshunter.h"
#include "worker.h"

#include <memory>
#include <WinSock2.h>
#include <MSWSock.h>

IocpServer::IocpServer()
{
    _wsa_inited = false;
    _socket     = INVALID_SOCKET;
    _msg_count  = 0;
    _client_count = 0;
}

IocpServer::~IocpServer()
{
}

int IocpServer::Init(const char *ip, unsigned short port, unsigned int nListen)
{
    int ret = 0;
    do {
        ret = WinSockInit();
    
        if (-1 == ret) {
            fprintf(stderr, "初始化WinSockInit失败\n");
            break;
        }

        _completion_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
        if (! _completion_port) {
            fprintf(stderr, "创建完成端口失败\n");
            ret = -1;
            break;
        }

        if (-1 == (ret = InitSocket())) {
            break;
        }

        if (-1 == (ret = Bind(ip, port))) {
            break;
        }

        if (-1 == (ret = Listen(nListen))) {
            break;
        }

        /*
        if (-1 == Accept()) {
            break;
        }
        */

       SocketExFnsHunter _socketExFunsHunter; 
       _acceptex_func = _socketExFunsHunter.AcceptEx;

        Workers *workers = new Workers(this); 
        workers->Start();

    } while(0);

    return ret;
}

int IocpServer::WinSockInit()
{
    int ret = -1;

    do {
        WORD version = MAKEWORD(2, 2);
        WSADATA wsaData;
        _wsa_inited = WSAStartup(version, &wsaData);
        if (_wsa_inited) { break; }

        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            WSACleanup();
            _wsa_inited = false;
            break;
        }
        ret = 0;
    } while(0);

    return ret;
}

int IocpServer::InitSocket()
{
    int ret = 0;

    do {
        // 创建服务器套接字，这里要注意最后一个参数必须为：WSA_FLAG_OVERLAPPED
        _socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

        if (_socket == INVALID_SOCKET) {
            fprintf(stderr, "创建WSASocket listnesocket失败\n");
            ret = -1;
            break;
        }

        if (! CreateIoCompletionPort(reinterpret_cast<HANDLE>(_socket), _completion_port, 0, 0)) {
            fprintf(stderr, "将listen socket关联到完成端口失败\n");
            ret = -1;
            break;
        }

    } while(0);

    return ret;
}


int IocpServer::Bind(const char *ip, unsigned short port)
{
    SOCKADDR_IN addr;
    addr.sin_addr.S_un.S_addr = inet_addr(ip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (::bind(_socket, (SOCKADDR *)&addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        fprintf(stderr, "bind 失败\n");
        return -1;
    }

    return 0;
}

int IocpServer::Listen(unsigned int nListen)
{
    if (::listen(_socket, nListen) == SOCKET_ERROR) {
        fprintf(stderr, "listen 失败\n");
        return -1;
    }

    return 0;
}


int IocpServer::Accept()
{
    int ret = -1;
    do {
		//这里我们不用WSAAccept，
		//因为我们需在查询完成端口的时候判断出，是accept、read、connect和write类型

		//WSAIoctl获取acceptex的函数地址
		//存放AcceptEx函数的指针

#if 0
        LPFN_ACCEPTEX _acceptex_func;
        GUID acceptex_guid = WSAID_ACCEPTEX;
        DWORD bytes_returned;

        ret = WSAIoctl(_socket, SIO_GET_EXTENSION_FUNCTION_POINTER,
            &acceptex_guid, sizeof(acceptex_guid),
            &_acceptex_func, sizeof(_acceptex_func),
            &bytes_returned, NULL, NULL);

        if (0 != ret) {
            ret = -1;
            fprintf(stderr, "获取AcceptEx函数地址失败\n");
            break;
        }

#endif
        SOCKET accept_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (accept_socket == INVALID_SOCKET) {
            fprintf(stderr, "初始化accept socket失败\n");
            ret = -1;
            break;
        }

		//这里设置Overlapped类型，到时查询完成端口的时候可以区别类型
        std::unique_ptr<Connection> new_connection(new Connection(accept_socket));

        DWORD bytes = 0;
        const int accept_ex_result = _acceptex_func(_socket, accept_socket,
                                    new_connection->GetReadBuffer(),
                                    0,
                                    sizeof(sockaddr_in) + 16, 
                                    sizeof(sockaddr_in) + 16,
                                    &bytes,
                                    reinterpret_cast<LPOVERLAPPED>
                                    (new_connection->GetAcceptOverlapped()));

        if (! (accept_ex_result == TRUE || WSAGetLastError() == WSA_IO_PENDING)) {
            ret = -1;
            fprintf(stderr, "调用AcceptEx 函数失败\n");
            break;
        }

        // 将accpet_socket关联到完成端口
        CreateIoCompletionPort(reinterpret_cast<HANDLE>(accept_socket),
                                _completion_port, 0, 0);

        /*
        std::unique_lock<mutex> gurad(mMutex);
        mConnectionVec.push_back(new_connection.get());
        gurad.unlock();
        */
        new_connection.release();

    } while (0);

    return ret;
}
void IocpServer::Run(const char *ip, unsigned short port, unsigned int nListen)
{
    if (Init(ip, port, nListen) == -1) {
        fprintf(stderr, "服务器启动失败\n");
        return;
    }

    Mainloop();
}

void IocpServer::Mainloop()
{
    //现在有工作者线程去处理业务，那主循环可以做点其他的事情了
	for (;;)
	{
		if (_chrono_timer.GetSecInterval() > 1.0)
		{
			fprintf(stderr, "client count<%d> msg count<%d>\n", _client_count, _msg_count);
			_chrono_timer.FlushTime();
			_msg_count = 0;
		}
	}


    /*
    DWORD bytes_transferred;
    ULONG_PTR completion_key;
    DWORD Flags = 0;
    Overlapped *overlapped = nullptr;

    while (1) {
        bool bRet = GetQueuedCompletionStatus(_completion_port,
                                 &bytes_transferred,
                                 &completion_key,
                                 reinterpret_cast<LPOVERLAPPED*>(&overlapped),
                                 INFINITE);

        if (bRet == false) {
            //客服端直接退出，没有调用closesocket正常关闭连接
            if (WAIT_TIMEOUT == GetLastError() || 
                ERROR_NETNAME_DELETED == GetLastError()) {

                // 客户端断开
                // fprintf(stderr, "client:%d 断开\n", 
                        // overlapped->connection->GetSocket());
 
                // delete overlapped->connection;
                // overlapped = nullptr;
                // continue;
            }
        }

        if (overlapped->type == Overlapped::Accept_Type) {
            //acceptex完成了操作，所以我们还要将其关联到完成端口。
			//这里先不改造，等后面我们会进行优化改造
			//我们也可以添加多个accept到完成端

            Accept();
            // 新客户端链接
            // fprintf(stderr, "新客户端加入\n");
            // AsyncRead(overlapped->connection);

            if (OnConnected) { OnConnected(overlapped->connection); }

            continue;
        }

        if (bytes_transferred == 0) {
            // 新客户端链接
            fprintf(stderr, "client:%d 断开\n", 
                    overlapped->connection->GetSocket());

            if (OnDisconnected) { OnDisconnected(overlapped->connection); }

            //TODO 先不进行内存管理
            // delete overlapped->connection;
            // overlapped = nullptr;
            // continue;
        }

        if (overlapped->type == Overlapped::Type::Read_Type) {
            // 异步读完成
            if (OnRead) { 
                OnRead(overlapped->connection, 
                       overlapped->connection->GetReadBuffer(),
                       bytes_transferred); 
            }
            continue;
        }

        if (overlapped->type == Overlapped::Type::Write_Type) {

            auto conn = overlapped->connection;
            conn->SetSentBytes(conn->GetSentBytes() + bytes_transferred);
            fprintf(stdout, "write type, client:%d, connect ID:%d\n",
                    overlapped->connection->GetSocket(),
                    overlapped->connection->GetID());

            // 判断是否只发送了一部分
            if (conn->GetSentBytes() < conn->GetTotalBytes()) {
                // 将剩余的部分在发送
                overlapped->wsa_buf.len = conn->GetTotalBytes() - conn->GetSentBytes();
                overlapped->wsa_buf.buf = reinterpret_cast<CHAR *>(
                                conn->GetWriteBuffer()) + conn->GetSentBytes();

                auto send_result = WSASend(conn->GetSocket(),
                                            &overlapped->wsa_buf, 1,
                                            &bytes_transferred,
                                            0,
                                reinterpret_cast<LPWSAOVERLAPPED>(overlapped),
                                            NULL);
                if (!(send_result == NULL || 
                        (send_result == SOCKET_ERROR && WSAGetLastError() == WSA_IO_PENDING))) {
                    fprintf(stderr, "发送数据失败\n");
                }
            } else {
                // 发送完成
                // AsyncRead(overlapped->connection);
                // conn->Clear();    

                if (OnWrite) { 
                    OnWrite(overlapped->connection, bytes_transferred); 
                }
            }
        }

    }
    */
}

void IocpServer::AsyncRead(const Connection *conn)
{
    auto overlapped = conn->GetReadOverlapped();
    overlapped->wsa_buf.len = overlapped->connection->GetReadBufferSize();
    overlapped->wsa_buf.buf = reinterpret_cast<CHAR*>(overlapped->connection->GetReadBuffer());
    
    DWORD flags = 0;
    DWORD bytes_transferred = 0;

    // 非阻塞收取数据，此时内核将数据推到应用层
    auto recv_result = WSARecv(overlapped->connection->GetSocket(),
                               &overlapped->wsa_buf, 1,
                               &bytes_transferred, &flags,
                               reinterpret_cast<LPWSAOVERLAPPED>(overlapped), 
                               NULL);

    if (!(recv_result == 0 || 
         (recv_result == SOCKET_ERROR && WSAGetLastError() == WSA_IO_PENDING))) {
        fprintf(stderr, "接收数据失败<AsyncRead>失败\n");
    }
}

void IocpServer::AsyncWrite(const Connection *conn, void *data, std::size_t size)
{
    /*
    std::unique_lock<mutex> guard(mMutex);
    do { 
        for (auto item : mConnectionVec) {
            auto mutable_conn = const_cast<Connection *>(item);

            char *send_msg = "I am server...";
            auto overlapped = mutable_conn->GetWriteOverlapped();
            overlapped->wsa_buff.len = strlen(send_msg);
            overlapped->wsa_buff.buf = send_msg;// reinterpret_cast<CHAR*>(mutable_conn->GetWriteBuffer());

            DWORD bytes;
            auto send_result = WSASend(mutable_conn->GetSocket(),
                                        &overlapped->wsa_buff, 1,
                                        &bytes, 0,
                                        reinterpret_cast<LPWSAOVERLAPPED>(overlapped),
                                        NULL);
        }
        
        if (mConnectionVec.size() >= 10 && guard.owns_lock()) { 
            guard.unlock(); 
        }

    } while (mConnectionVec.size() >= 10);

    if (guard.owns_lock()) { guard.unlock(); }
    */
    
    auto mutable_conn = const_cast<Connection *>(conn);
    if (mutable_conn->GetWriteBufferSize() < size) {
        mutable_conn->ResizeWriteBuffer(size);
    }

    memcpy_s(mutable_conn->GetWriteBuffer(), 
                mutable_conn->GetWriteBufferSize(), data, size);
    mutable_conn->SetSentBytes(0);
    mutable_conn->SetTotalBytes(size);

    auto overlapped = mutable_conn->GetWriteOverlapped();
    overlapped->wsa_buf.len = size;
    overlapped->wsa_buf.buf = reinterpret_cast<CHAR*>(mutable_conn->GetWriteBuffer());

    DWORD bytes;
    auto send_result = WSASend(mutable_conn->GetSocket(),
                                &overlapped->wsa_buf, 1,
                                &bytes, 0,
                                reinterpret_cast<LPWSAOVERLAPPED>(overlapped),
                                NULL);
    if (!(send_result == 0 || 
        (send_result == SOCKET_ERROR && WSAGetLastError() == WSA_IO_PENDING))) {
        fprintf(stderr, "发送数据失败\n");
    }
}
