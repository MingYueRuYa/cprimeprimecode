/****************************************************************************
**
** Copyright (C) 2017 上海奕想网络科技有限公司. (http://www.2144.cn)
** All rights reserved.
**
****************************************************************************/

#include "basethread.h"

DWORD WINAPI BaseThread::ThreadProcess(LPVOID p_lpParameter)
{
	BaseThread *basethread = (BaseThread *)p_lpParameter;
	if (NULL == basethread) {
		return -1;
	}
	basethread->Run();

	return 0;
}

BaseThread::BaseThread()
{
	m_Parameter = NULL;
	m_IsStop	= false;
	m_ThreadID	= 0;
	m_ThreadHandle	 = NULL;
	m_lpExtraParameter = NULL;
}

BaseThread::~BaseThread()
{
	Stop();
}

bool BaseThread::GetIsStop()
{
	return m_IsStop;
}

void BaseThread::Start()
{
	m_ThreadHandle = CreateThread(NULL, 0, ThreadProcess, (LPVOID)this, 0, &m_ThreadID);
}

void BaseThread::Stop()
{
	if (NULL == m_ThreadHandle) {
		return;
	}
	 
	m_IsStop = true;
	WaitForSingleObject(m_ThreadHandle, INFINITE);
	CloseHandle(m_ThreadHandle);
	m_ThreadHandle = NULL;
}

void BaseThread::SetExtraParameter(LPVOID p_lpParameter)
{
	m_lpExtraParameter = p_lpParameter;
}

LPVOID BaseThread::GetExtraParameter()
{
	return m_lpExtraParameter;
}

void BaseThread::Run()
{
}