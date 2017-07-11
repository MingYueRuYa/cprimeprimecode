/****************************************************************************
**
** Copyright (C) 2017 上海奕想网络科技有限公司. (http://www.2144.cn)
** All rights reserved.
**
****************************************************************************/

#ifndef basethread_h
#define basethread_h

#include <windows.h>

/*! \brief BaseThread
 	\author liushixiong (liushixiong@2144.cn)
 	\version 0.01
 	\date 2017/04/25
	
	线程基类，只能满足基本使用，有待完善
*/
class BaseThread
{
public:
	static DWORD WINAPI ThreadProcess(LPVOID p_lpParameter);

public:
	BaseThread();

	virtual ~BaseThread();

	bool GetIsStop();
	
	void Start();

	void Stop();

	void SetExtraParameter(LPVOID p_lpParameter);
	LPVOID GetExtraParameter();

	virtual void Run();

protected:
	void *m_Parameter;

	bool m_IsStop;

	DWORD m_ThreadID;

	HANDLE m_ThreadHandle;

	LPVOID m_lpExtraParameter;

};

#endif //basethread_h