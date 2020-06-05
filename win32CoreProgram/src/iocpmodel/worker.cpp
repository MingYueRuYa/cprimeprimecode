#include "worker.h"
#include "overlapped.h"
#include "socketexfunshunter.h"

#include <stdio.h>
#include <assert.h>
#include <WinSock2.h>
#include <Windows.h>

DWORD WINAPI ServerWorkerThread(LPVOID p)
{
    assert(p);

    auto workers = (Workers*)p;
    workers->ThreadProc();
    return 0;
}

Workers::Workers(IocpServer *server)
{
    _iocpServer = const_cast<IocpServer *>(server);
}

void Workers::Start()
{
    SYSTEM_INFO systeminfo;
    ::GetSystemInfo(&systeminfo);
    
    for (unsigned long i = 0; i < systeminfo.dwNumberOfProcessors * 2; ++i) {
        DWORD thread_id;
        HANDLE thread_handle = ::CreateThread(NULL, 0, ServerWorkerThread, this, 0, &thread_id);
        if (NULL == thread_handle) { 
            printf("CreateThread() failed with error %d\n", GetLastError());
            return; 
        }

        ::CloseHandle(thread_handle);
    }

    _iocpServer->Accept();
}

void Workers::ThreadProc()
{
    DWORD bytes_transferred;
    ULONG_PTR completion_key;
    DWORD flags = 0;
    Overlapped *overlapped = NULL;

    while (1) {

        BOOL ret = GetQueuedCompletionStatus(_iocpServer->_completion_port, 
                                                &bytes_transferred,
                                                &completion_key,
                                                reinterpret_cast<LPOVERLAPPED*>(&overlapped),
                                                INFINITE);

        if (ret == FALSE) {
            if (WAIT_TIMEOUT == GetLastError() || ERROR_NETNAME_DELETED == GetLastError()) {
                if (nullptr != overlapped) {
                    if (nullptr != overlapped->connection) {
                        if (_iocpServer->OnDisconnected) {
                            _iocpServer->OnDisconnected(overlapped->connection);

                            // delete overlapped->connection;
                            // continue;
                        }
                    }
                }
            }            
        } else {
            if (Overlapped::Accept_Type == overlapped->type) {
                _iocpServer->Accept();

                // 新客户端链接
                if (_iocpServer->OnConnected) {
                    _iocpServer->OnConnected(overlapped->connection);
                }

                continue;
            }

            if (0 == bytes_transferred) {
                if (overlapped->connection != NULL) {
                    if (_iocpServer->OnDisconnected) {
                        _iocpServer->OnDisconnected(overlapped->connection);

                        delete overlapped->connection;
                        overlapped->connection = nullptr;
                        overlapped = nullptr;
                    }
                }
                continue;
            }


            if (Overlapped::Read_Type == overlapped->type) {
                if (_iocpServer->OnRead) {
                    _iocpServer->OnRead(overlapped->connection, overlapped->connection->GetReadBuffer(), bytes_transferred);
                }

                continue;
            }

            if (overlapped->type == Overlapped::Type::Write_Type)
			{
				auto conn = overlapped->connection;
				conn->SetSentBytes(conn->GetSentBytes() + bytes_transferred);

				//判断是否只发送了一部分
				if (conn->GetSentBytes() < conn->GetTotalBytes())
				{
					//将剩余部分再发送
					overlapped->wsa_buf.len = conn->GetTotalBytes() - conn->GetSentBytes();
					overlapped->wsa_buf.buf = reinterpret_cast<CHAR*>(conn->GetWriteBuffer()) + conn->GetSentBytes();

					auto send_result = WSASend(conn->GetSocket(),
						&overlapped->wsa_buf, 1, &bytes_transferred,
						0, reinterpret_cast<LPWSAOVERLAPPED>(overlapped),
						NULL);

					if (!(send_result == NULL || (send_result == SOCKET_ERROR && WSAGetLastError() == WSA_IO_PENDING)))
						fprintf(stderr, "发送数据失败\n");
				}
				else
				{
					//发送完成
					//AsyncRead(overlapped->connection);
					if (_iocpServer->OnWrite)
						_iocpServer->OnWrite(overlapped->connection, bytes_transferred);
				}
			}

        }

    }
}
