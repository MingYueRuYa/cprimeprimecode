/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef iocpserver_h
#define iocpserver_h

#include <list>
#include <string>
#include <winsock2.h>
#include <MSWSock.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER_LEN	8192
#define DEFAULT_PORT	12345
#define DEFAULT_IP		("127.0.0.1")

using std::list;
using std::string;

typedef enum _OPERATION_TYPE
{
	ACCEPT_POSTED,
	SEND_POSTED,
	RECV_POSTED,
	NULL_POSTED
} OPERATION_TYPE;

typedef struct _PER_IO_CONTEXT
{
	// 这个字段需要放到第一个位置
	OVERLAPPED		m_Overlapped;
	SOCKET			m_sockAccept;
	WSABUF			m_wsaBuf;
	char			m_szBuffer[MAX_BUFFER_LEN];
	OPERATION_TYPE	m_OpType;

	// 初始化
	_PER_IO_CONTEXT()
	{
		ZeroMemory(&m_Overlapped, sizeof(OVERLAPPED));
		ZeroMemory(m_szBuffer, MAX_BUFFER_LEN);
		m_sockAccept = INVALID_SOCKET;
		m_wsaBuf.buf = m_szBuffer;
		m_wsaBuf.len = MAX_BUFFER_LEN;
		m_OpType	 = NULL_POSTED;
	}

	~_PER_IO_CONTEXT()
	{
		if (m_sockAccept != INVALID_SOCKET) {
			closesocket(m_sockAccept);
			m_sockAccept = INVALID_SOCKET;
		}
	}

	void ResetBuffer()
	{
		ZeroMemory(m_szBuffer, MAX_BUFFER_LEN);
	}

}PER_IO_CONTEXT, *PPER_IO_CONTEXT;

typedef struct _PER_SOCKET_CONTEXT
{
	SOCKET m_Socket;
	SOCKADDR_IN m_ClientAddr;
	list<_PER_IO_CONTEXT *> m_listIoContext;
	
	_PER_SOCKET_CONTEXT()
	{
		m_Socket = INVALID_SOCKET;
		memset(&m_ClientAddr, 0, sizeof(m_ClientAddr));
	}

	~_PER_SOCKET_CONTEXT()
	{
		if (m_Socket != INVALID_SOCKET) {
			closesocket(m_Socket);
			m_Socket = INVALID_SOCKET;
		}
		
		list<PER_IO_CONTEXT *>::iterator ibeg = m_listIoContext.begin();
		for (; ibeg != m_listIoContext.end(); ++ibeg) {
			delete *ibeg;
		}
		m_listIoContext.clear();
	}

	_PER_IO_CONTEXT *GetNewIoContext()
	{
		_PER_IO_CONTEXT *newio = new _PER_IO_CONTEXT();
		m_listIoContext.push_back(newio);
		return newio;
	}

	void RemoveContext(_PER_IO_CONTEXT *pContext)
	{
		list<PER_IO_CONTEXT *>::iterator ibeg = m_listIoContext.begin();
		for (; ibeg != m_listIoContext.end(); ++ibeg) {
			if (*ibeg != pContext) {
				continue;
			}
			m_listIoContext.erase(ibeg);
			break;
		}
	}
		
}PER_SOCKET_CONTEXT, *PPER_SOCKET_CONTEXT;

class IOCPServer;

typedef struct _tagThreadParams_WORKER
{
	IOCPServer *pIOCPServer;
	int nThreadNo;
}THREADPARAMS_WORKER, *PTHREADPARAMS_WORKER;

class IOCPServer
{
public:
	IOCPServer();
	~IOCPServer();

public:
	bool Start();
	void Stop();

	bool LoadSocketLib();
	void UnLoadSocketLib() { WSACleanup(); }

	string GetLocalIP();

	void SetPort(const int &nPort) { m_nPort = nPort; }

protected:
	bool _InitializeIOCP();
	bool _InitializeListenSocket();
	void _DeInitialize();
	bool _PostAccept(PER_IO_CONTEXT *pAcceptIoContext);
	bool _PostRecv(PER_IO_CONTEXT *pIoContext);
	bool _DoAccept(PER_SOCKET_CONTEXT *pSocketContext, 
					PER_IO_CONTEXT *pIoContext);
	bool _DoRecv(PER_SOCKET_CONTEXT *pSocketContext, 
					PER_IO_CONTEXT *pIoContext);
	void _AddToContextList(PER_SOCKET_CONTEXT *pSocketContext);
	void _RemoveContext(PER_SOCKET_CONTEXT *pSocketContext);
	void _ClearContextList();
	bool _AssociateWithIOCP(PER_SOCKET_CONTEXT *pContext);
	bool HandleError(PER_SOCKET_CONTEXT *pContext, const DWORD &dwErr);
	
	static DWORD WINAPI _WorkerThread(LPVOID lpParam);
	
	int _GetNoOfProcessors();
	bool _IsSocketAlive(SOCKET s);

private:
	HANDLE m_hShutdownEvent;
	HANDLE m_hIOCompletionPort;
	HANDLE *m_phWorkerThreads;

	int		m_nThreads;
	int		m_nPort;
	string	m_strIP;
	CRITICAL_SECTION			m_csContextList;
	list<PER_SOCKET_CONTEXT *>	m_listClientContext;
	PER_SOCKET_CONTEXT*			m_pListenContext;
	LPFN_ACCEPTEX				m_lpfnAcceptEx;
	LPFN_GETACCEPTEXSOCKADDRS	m_lpfnGetAcceptExSockAddrs;
};

#endif // iocpserver_h