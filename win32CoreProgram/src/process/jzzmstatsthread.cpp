/****************************************************************************
**
** Copyright (C) 2017 上海奕想网络科技有限公司. (http://www.2144.cn)
** All rights reserved.
**
****************************************************************************/

WM_USER

#include "jzzmstatsthread.h"

const int SLEEP_TIME = 500;

jzzmStatsThread::jzzmStatsThread()
{
	//mMutexHandle = CreateMutex(NULL, false, NULL);
	InitializeCriticalSectionAndSpinCount(&mCriticalSection, 0x00000400);
	mSemaphoreHandle = CreateSemaphore(NULL, 0, 1, NULL);
}

jzzmStatsThread::~jzzmStatsThread()
{
	if (NULL != mSemaphoreHandle) {
		CloseHandle(mSemaphoreHandle);
	}

	DeleteCriticalSection(&mCriticalSection);
}

void jzzmStatsThread::Apppend(const wstring pStrUrl)
{
	EnterCriticalSection(&mCriticalSection);
	//WaitForSingleObject(mMutexHandle, INFINITE);
	mStatsCommandList.push_back(pStrUrl);
	//ReleaseMutex(mMutexHandle);
	LeaveCriticalSection(&mCriticalSection);
}

void jzzmStatsThread::Run()
{
	while (! m_IsStop) {	
		WaitForSingleObject(mSemaphoreHandle, INFINITE);
		if (mStatsCommandList.empty()) {
		}
		else {
			EnterCriticalSection(&mCriticalSection);
			mStatsCommandList.pop_front();
			LeaveCriticalSection(&mCriticalSection);
			//TODO 发送网络数据
		}
	} //while
}
