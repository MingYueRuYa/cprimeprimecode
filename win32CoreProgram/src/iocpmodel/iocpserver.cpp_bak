#define _WINSOCK_DEPRECATED_NO_WARNINGS

/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "iocpserver.h"

#include <iostream>

using std::cout;
using std::endl;

// 每一个处理器上产生多少个线程(为了最大限度的提升服务器性能，详见配套文档)
#define WORKER_THREADS_PER_PROCESSOR 2
// 同时投递的Accept请求的数量(这个要根据实际的情况灵活设置)
#define MAX_POST_ACCEPT              10
// 传递给Worker线程的退出信号
#define EXIT_CODE                    NULL

// 释放指针宏
#define RELEASE(x)                      {if(x != NULL ){delete x;x=NULL;}}
// 释放句柄宏
#define RELEASE_HANDLE(x)               {if(x != NULL && x!=INVALID_HANDLE_VALUE){ CloseHandle(x);x = NULL;}}
// 释放Socket宏
#define RELEASE_SOCKET(x)				{if(x !=INVALID_SOCKET) \
										 { closesocket(x);x=INVALID_SOCKET;}}

IOCPServer::IOCPServer(void):
							m_nThreads(0),
							m_hShutdownEvent(NULL),
							m_hIOCompletionPort(NULL),
							m_phWorkerThreads(NULL),
							m_strIP(DEFAULT_IP),
							m_nPort(DEFAULT_PORT),
							m_lpfnAcceptEx( NULL ),
							m_pListenContext( NULL )
{
}

IOCPServer::~IOCPServer(void)
{
	// 确保资源彻底释放
	this->Stop();
}

DWORD WINAPI IOCPServer::_WorkerThread(LPVOID lpParam)
{
	THREADPARAMS_WORKER *pParam = (THREADPARAMS_WORKER*)lpParam;
	IOCPServer *iocpServer		= pParam->pIOCPServer;
	int threadno				= pParam->nThreadNo;

	cout << "worker thread start " << threadno << endl;

	OVERLAPPED *pOverlapped				= nullptr;
	DWORD dwBytesTransfered				= 0;
	PER_SOCKET_CONTEXT *pSocketContext	= nullptr;

	// 循环处理请求，直到收到shutdown信息为止
	while (WAIT_OBJECT_0 != WaitForSingleObject(iocpServer->m_hShutdownEvent, 
		0)) {
		BOOL bReturn = GetQueuedCompletionStatus(
											iocpServer->m_hIOCompletionPort,
											&dwBytesTransfered,
											(PULONG_PTR)&pSocketContext,
											&pOverlapped,
											INFINITE);
		if (EXIT_CODE == (DWORD)pSocketContext) {
			break;
		}

		if (! bReturn) {
			DWORD dwErr = GetLastError();
			if (! iocpServer->HandleError(pSocketContext, dwErr)) {
				break;
			}
			continue;
		} else {
			// 读取参数
			PER_IO_CONTEXT *pIoContext = CONTAINING_RECORD(pOverlapped,
															PER_IO_CONTEXT,
															m_Overlapped);

			if ((0 == dwBytesTransfered) && 
				(RECV_POSTED == pIoContext->m_OpType || 
				SEND_POSTED == pIoContext->m_OpType)) {
				cout << "client diconnected:" 
					 << inet_ntoa(pSocketContext->m_ClientAddr.sin_addr) 
					 << " port:" << ntohs(pSocketContext->m_ClientAddr.sin_port)
					 << endl;
			} else {
				switch(pIoContext->m_OpType)
				{
				case ACCEPT_POSTED:
					iocpServer->_DoAccept(pSocketContext, pIoContext);
					break;
				case RECV_POSTED:
					iocpServer->_DoRecv(pSocketContext, pIoContext);
					break;
				case SEND_POSTED:
					break;
				default:
					break;
				}
			}
		} // if bReturn

	} // while

	cout << "work thread exit " << threadno << endl;

	return 0;
}


bool IOCPServer::LoadSocketLib()
{
	WSADATA wsaData;
	int nResult;
	nResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	// 错误(一般都不可能出现)
	if (NO_ERROR != nResult)
	{
		cout << "load socket lib error" << endl;
		return false; 
	}

	return true;
}

bool IOCPServer::Start()
{
		// 初始化线程互斥量
	InitializeCriticalSection(&m_csContextList);

	// 建立系统退出的事件通知
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// 初始化IOCP
	if (false == _InitializeIOCP())
	{
		cout << "初始化IOCP失败！" << endl;
		return false;
	}
	else
	{
		cout << "初始化IOCP成功" << endl;
	}

	// 初始化Socket
	if( false==_InitializeListenSocket() )
	{
		cout << "Listen Socket初始化失败！" << endl;
		this->_DeInitialize();
		return false;
	}
	else
	{
		cout << "Listen Socket初始化完毕." << endl;
	}

	cout << "系统准备就绪，等候连接...." << endl;

	return true;
}

////////////////////////////////////////////////////////////////////
//	开始发送系统退出消息，退出完成端口和线程资源
void IOCPServer::Stop()
{
	if( m_pListenContext!=NULL && m_pListenContext->m_Socket!=INVALID_SOCKET )
	{
		// 激活关闭消息通知
		SetEvent(m_hShutdownEvent);

		for (int i = 0; i < m_nThreads; i++)
		{
			// 通知所有的完成端口操作退出
			PostQueuedCompletionStatus(m_hIOCompletionPort, 0, (DWORD)EXIT_CODE, NULL);
		}

		// 等待所有的客户端资源退出
		WaitForMultipleObjects(m_nThreads, m_phWorkerThreads, TRUE, INFINITE);

		// 清除客户端列表信息
		this->_ClearContextList();

		// 释放其他资源
		this->_DeInitialize();

		cout << "停止监听" <<endl;
	}	
}

////////////////////////////////
// 初始化完成端口
bool IOCPServer::_InitializeIOCP()
{
	// 建立第一个完成端口
	m_hIOCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0 );

	if ( NULL == m_hIOCompletionPort)
	{
		cout << "建立完成端口失败！错误代码: %d!\n" << endl;
		return false;
	}

	// 根据本机中的处理器数量，建立对应的线程数
	m_nThreads = WORKER_THREADS_PER_PROCESSOR * _GetNoOfProcessors();
	
	// 为工作者线程初始化句柄
	m_phWorkerThreads = new HANDLE[m_nThreads];
	
	// 根据计算出来的数量建立工作者线程
	DWORD nThreadID;
	for (int i = 0; i < m_nThreads; i++)
	{
		THREADPARAMS_WORKER* pThreadParams	= new THREADPARAMS_WORKER;
		pThreadParams->pIOCPServer			= this;
		pThreadParams->nThreadNo			= i+1;
		m_phWorkerThreads[i]				 = ::CreateThread(0, 0,
														_WorkerThread, 
														(void *)pThreadParams, 
														0, 
														&nThreadID);
	}

	cout << " 建立 _WorkerThread %d 个.\n" << endl;

	return true;
}

// 初始化Socket
bool IOCPServer::_InitializeListenSocket()
{
	GUID GuidAcceptEx				= WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockAddrs	= WSAID_GETACCEPTEXSOCKADDRS;

	struct sockaddr_in ServerAddress;
	m_pListenContext = new PER_SOCKET_CONTEXT;
	m_pListenContext->m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 
											WSA_FLAG_OVERLAPPED);

	if (INVALID_SOCKET == m_pListenContext->m_Socket) 
	{
		cout << "初始化Socket失败，错误代码: " << WSAGetLastError() << endl;
		return false;
	}
	else
	{
		cout << "WSASocket() 完成"  << endl;
	}

	HANDLE hresult = CreateIoCompletionPort((HANDLE)m_pListenContext->m_Socket,
							m_hIOCompletionPort, (DWORD)m_pListenContext, 0);

	if (hresult == nullptr) {  
		cout << "绑定 Listen Socket至完成端口失败！错误代码: " << WSAGetLastError()
			 << endl;
		RELEASE_SOCKET( m_pListenContext->m_Socket );
		return false;
	}
	else
	{
		cout << "Listen Socket绑定完成端口 完成"  << endl;
	}

	// 填充地址信息
	ZeroMemory((char *)&ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	// 这里可以绑定任何可用的IP地址，或者绑定一个指定的IP地址 
	//ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);                      
	ServerAddress.sin_addr.s_addr = inet_addr(m_strIP.c_str());         
	ServerAddress.sin_port = htons(m_nPort);  

		// 绑定地址和端口
	if (SOCKET_ERROR == bind(m_pListenContext->m_Socket, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress))) 
	{
		cout << "bind()函数执行错误" << endl;
		return false;
	}
	else
	{
		cout << "bind() 完成" << endl;
	}

	// 开始进行监听
	if (SOCKET_ERROR == listen(m_pListenContext->m_Socket,SOMAXCONN))
	{
		cout << "Listen()函数执行出现错误" << endl;
		return false;
	}
	else
	{
		cout << "Listen() 完成" << endl;
	}

	// 使用AcceptEx函数，因为这个是属于WinSock2规范之外的微软另外提供的扩展函数
	// 所以需要额外获取一下函数的指针，
	// 获取AcceptEx函数指针
	DWORD dwBytes = 0;  
	if(SOCKET_ERROR == WSAIoctl(
		m_pListenContext->m_Socket, 
		SIO_GET_EXTENSION_FUNCTION_POINTER, 
		&GuidAcceptEx, 
		sizeof(GuidAcceptEx), 
		&m_lpfnAcceptEx, 
		sizeof(m_lpfnAcceptEx), 
		&dwBytes, 
		NULL, 
		NULL))  
	{  
		cout << "WSAIoctl 未能获取AcceptEx函数指针。错误代码: " 
			 << WSAGetLastError()
			 << endl;
		this->_DeInitialize();
		return false;  
	}  

	// 获取GetAcceptExSockAddrs函数指针，也是同理
	if(SOCKET_ERROR == WSAIoctl(
		m_pListenContext->m_Socket, 
		SIO_GET_EXTENSION_FUNCTION_POINTER, 
		&GuidGetAcceptExSockAddrs,
		sizeof(GuidGetAcceptExSockAddrs), 
		&m_lpfnGetAcceptExSockAddrs, 
		sizeof(m_lpfnGetAcceptExSockAddrs),   
		&dwBytes, 
		NULL, 
		NULL))  
	{  
		cout << "WSAIoctl 未能获取GuidGetAcceptExSockAddrs函数指针。错误代码: " 
			 << WSAGetLastError()
			 << endl;
		this->_DeInitialize();
		return false; 
	}  

	// 为AcceptEx 准备参数，然后投递AcceptEx I/O请求
	for( int i=0;i<MAX_POST_ACCEPT;i++ )
	{
		// 新建一个IO_CONTEXT
		PER_IO_CONTEXT* pAcceptIoContext = m_pListenContext->GetNewIoContext();

		if( false==this->_PostAccept( pAcceptIoContext ) )
		{
			m_pListenContext->RemoveContext(pAcceptIoContext);
			return false;
		}
	}

	cout << "投递 10 个AcceptEx请求完毕" << endl;
	return true;
}

////////////////////////////////////////////////////////////
//	最后释放掉所有资源
void IOCPServer::_DeInitialize()
{
	// 删除客户端列表的互斥量
	DeleteCriticalSection(&m_csContextList);

	// 关闭系统退出事件句柄
	RELEASE_HANDLE(m_hShutdownEvent);

	// 释放工作者线程句柄指针
	for( int i=0;i<m_nThreads;i++ )
	{
		RELEASE_HANDLE(m_phWorkerThreads[i]);
	}
	
	RELEASE(m_phWorkerThreads);

	// 关闭IOCP句柄
	RELEASE_HANDLE(m_hIOCompletionPort);

	// 关闭监听Socket
	RELEASE(m_pListenContext);

	cout << "释放资源完毕" << endl;
}

// 投递Accept请求
bool IOCPServer::_PostAccept( PER_IO_CONTEXT* pAcceptIoContext)
{
	DWORD dwBytes = 0;
	pAcceptIoContext->m_OpType = ACCEPT_POSTED;
	WSABUF *p_wbuf		= &pAcceptIoContext->m_wsaBuf;
	OVERLAPPED *p_ol	= &pAcceptIoContext->m_Overlapped;

	// 为以后新连入的客户端先准备好Socket( 这个是与传统accept最大的区别 ) 
	pAcceptIoContext->m_sockAccept  = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);  
	if( INVALID_SOCKET==pAcceptIoContext->m_sockAccept )  
	{  
		cout << "创建用于Accept的Socket失败！错误代码: " 
			 << WSAGetLastError() << endl;
		return false;  
	} 

	bool result = m_lpfnAcceptEx(m_pListenContext->m_Socket, 
									pAcceptIoContext->m_sockAccept,
									p_wbuf->buf, 
									p_wbuf->len-(sizeof(SOCKADDR_IN)+16)*2,
									sizeof(SOCKADDR_IN)+16,
									sizeof(SOCKADDR_IN)+16, &dwBytes, p_ol);
	if (! result) {
		if(WSA_IO_PENDING != WSAGetLastError())  
		{  
			cout << "投递 AcceptEx 请求失败，错误代码: " << WSAGetLastError() << endl;
			return false; 
		} 
	}

	return true;
}

bool IOCPServer::_DoAccept( PER_SOCKET_CONTEXT* pSocketContext, 
							PER_IO_CONTEXT* pIoContext)
{
	SOCKADDR_IN* ClientAddr = NULL;
	SOCKADDR_IN* LocalAddr = NULL;  
	int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);  

			///////////////////////////////////////////////////////////////////////////
	// 1. 首先取得连入客户端的地址信息
	// 这个 m_lpfnGetAcceptExSockAddrs 不得了啊~~~~~~
	// 不但可以取得客户端和本地端的地址信息，还能顺便取出客户端发来的第一组数据，老强大了...
	m_lpfnGetAcceptExSockAddrs(pIoContext->m_wsaBuf.buf, 
						pIoContext->m_wsaBuf.len-(sizeof(SOCKADDR_IN)+16)*2,
						sizeof(SOCKADDR_IN)+16, 
						sizeof(SOCKADDR_IN)+16,
						(LPSOCKADDR *)&LocalAddr,
						&localLen,
						(LPSOCKADDR *)&ClientAddr,
						&remoteLen
						);
	cout << "客户端 " << inet_ntoa(ClientAddr->sin_addr) << " " 
		 <<  ntohs(ClientAddr->sin_port) << " " << pIoContext->m_wsaBuf.buf 
		 << " 连入." << endl;

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2. 这里需要注意，这里传入的这个是ListenSocket上的Context，这个Context我们还需要用于监听下一个连接
	// 所以我还得要将ListenSocket上的Context复制出来一份为新连入的Socket新建一个SocketContext
	PER_SOCKET_CONTEXT *pNewSocketContext = new PER_SOCKET_CONTEXT();
	pNewSocketContext->m_Socket = pIoContext->m_sockAccept;		 
	memcpy(&(pNewSocketContext->m_ClientAddr), ClientAddr, sizeof(SOCKADDR_IN));

	if (false == this->_AssociateWithIOCP(pNewSocketContext)) {
		RELEASE(pNewSocketContext);
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// 3. 继续，建立其下的IoContext，用于在这个Socket上投递第一个Recv数据请求
	PER_IO_CONTEXT *pNewIoContext	= pNewSocketContext->GetNewIoContext();
	pNewIoContext->m_OpType			= RECV_POSTED;
	pNewIoContext->m_sockAccept		= pNewSocketContext->m_Socket;

	if (false == this->_PostRecv(pNewIoContext)) {
		pNewSocketContext->RemoveContext(pNewIoContext);
		return false;
	}

	this->_AddToContextList(pNewSocketContext);

	pIoContext->ResetBuffer();
	return this->_PostAccept(pIoContext);
}

////////////////////////////////////////////////////////////////////
// 投递接收数据请求
bool IOCPServer::_PostRecv( PER_IO_CONTEXT* pIoContext )
{
	DWORD dwFlags = 0;
	DWORD dwBytes = 0;

	WSABUF *p_wbuf		= &pIoContext->m_wsaBuf;
	OVERLAPPED *p_ol	= &pIoContext->m_Overlapped;
	
	pIoContext->ResetBuffer();
	pIoContext->m_OpType = RECV_POSTED;
	int nBytesRecv = WSARecv(pIoContext->m_sockAccept, p_wbuf, 1, &dwBytes,
								&dwFlags, p_ol, NULL);	
	
	if ((SOCKET_ERROR == nBytesRecv) && (WSA_IO_PENDING != WSAGetLastError())) {
		cout << "post recv error" << endl;
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////
// 在有接收的数据到达的时候，进行处理
bool IOCPServer::_DoRecv( PER_SOCKET_CONTEXT* pSocketContext, PER_IO_CONTEXT* pIoContext )
{
	// 先把上一次的数据显示出现，然后就重置状态，发出下一个Recv请求
	SOCKADDR_IN* ClientAddr = &pSocketContext->m_ClientAddr;

	cout << "收到：" << inet_ntoa(ClientAddr->sin_addr) << ":" << ntohs(ClientAddr->sin_port) << " " << pIoContext->m_wsaBuf.buf << endl;

	// 然后开始投递下一个WSARecv请求
	return _PostRecv( pIoContext );
}

/////////////////////////////////////////////////////
// 将句柄(Socket)绑定到完成端口中
bool IOCPServer::_AssociateWithIOCP( PER_SOCKET_CONTEXT *pContext )
{
	// 将用于和客户端通信的SOCKET绑定到完成端口中
	HANDLE hTemp = CreateIoCompletionPort((HANDLE)pContext->m_Socket, m_hIOCompletionPort, (DWORD)pContext, 0);

	if (NULL == hTemp)
	{
		cout << "执行CreateIoCompletionPort()出现错误.错误代码：" 
			 << GetLastError() << endl;
		return false;
	}

	return true;
}

//====================================================================================
//
//				    ContextList 相关操作
//
//====================================================================================


//////////////////////////////////////////////////////////////
// 将客户端的相关信息存储到数组中
void IOCPServer::_AddToContextList( PER_SOCKET_CONTEXT *pHandleData )
{
	EnterCriticalSection(&m_csContextList);

	m_listClientContext.push_back(pHandleData);
	
	LeaveCriticalSection(&m_csContextList);
}

////////////////////////////////////////////////////////////////
//	移除某个特定的Context
void IOCPServer::_RemoveContext( PER_SOCKET_CONTEXT *pSocketContext )
{
	EnterCriticalSection(&m_csContextList);

	/*
	for( int i=0;i<m_arrayClientContext.GetCount();i++ )
	{
		if( pSocketContext==m_arrayClientContext.GetAt(i) )
		{
			RELEASE( pSocketContext );			
			m_arrayClientContext.RemoveAt(i);			
			break;
		}
	}
	*/
	LeaveCriticalSection(&m_csContextList);
}

////////////////////////////////////////////////////////////////
// 清空客户端信息
void IOCPServer::_ClearContextList()
{
	EnterCriticalSection(&m_csContextList);

	/*
	for( int i=0;i<m_arrayClientContext.GetCount();i++ )
	{
		delete m_arrayClientContext.GetAt(i);
	}

	m_arrayClientContext.RemoveAll();
	*/

	LeaveCriticalSection(&m_csContextList);
}

////////////////////////////////////////////////////////////////////
// 获得本机的IP地址
string IOCPServer::GetLocalIP()
{
	// 获得本机主机名
	char hostname[MAX_PATH] = {0};
	gethostname(hostname,MAX_PATH);                
	struct hostent FAR* lpHostEnt = gethostbyname(hostname);
	if(lpHostEnt == NULL)
	{
		return DEFAULT_IP;
	}

	// 取得IP地址列表中的第一个为返回的IP(因为一台主机可能会绑定多个IP)
	LPSTR lpAddr = lpHostEnt->h_addr_list[0];      

	// 将IP地址转化成字符串形式
	struct in_addr inAddr;
	memmove(&inAddr,lpAddr,4);
	m_strIP = inet_ntoa(inAddr);        

	return m_strIP;
}

///////////////////////////////////////////////////////////////////
// 获得本机中处理器的数量
int IOCPServer::_GetNoOfProcessors()
{
	SYSTEM_INFO si;

	GetSystemInfo(&si);

	return si.dwNumberOfProcessors;
}

/////////////////////////////////////////////////////////////////////
// 判断客户端Socket是否已经断开，否则在一个无效的Socket上投递WSARecv操作会出现异常
// 使用的方法是尝试向这个socket发送数据，判断这个socket调用的返回值
// 因为如果客户端网络异常断开(例如客户端崩溃或者拔掉网线等)的时候，服务器端是无法收到客户端断开的通知的

bool IOCPServer::_IsSocketAlive(SOCKET s)
{
	int nByteSent=send(s,"",0,0);
	if (-1 == nByteSent) return false;
	return true;
}

///////////////////////////////////////////////////////////////////
// 显示并处理完成端口上的错误
bool IOCPServer::HandleError( PER_SOCKET_CONTEXT *pContext,const DWORD& dwErr )
{
	// 如果是超时了，就再继续等吧  
	if(WAIT_TIMEOUT == dwErr)  
	{  	
		// 确认客户端是否还活着...
		if( !_IsSocketAlive( pContext->m_Socket) )
		{
			cout << "检测到客户端异常退出！" << endl;
			this->_RemoveContext( pContext );
			return true;
		}
		else
		{
			cout << "网络操作超时！重试中..." << endl;
			return true;
		}
	}  

	// 可能是客户端异常退出了
	else if( ERROR_NETNAME_DELETED==dwErr )
	{
		cout << "检测到客户端异常退出！" << endl;
		this->_RemoveContext( pContext );
		return true;
	}

	else
	{
		cout << "完成端口操作出现错误，线程退出。错误代码：" << dwErr << endl;
		return false;
	}
}