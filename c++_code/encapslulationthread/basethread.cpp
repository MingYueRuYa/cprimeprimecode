/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include "basethread.h"

using std::cout;
using std::endl;

void *BaseThread::Run(void *pArg)
{
	BaseThread *basethread = (BaseThread *)(pArg);
	basethread->Execute();
	pthread_exit(0);
}

BaseThread::BaseThread()
{
	mPid = -1;
}

BaseThread::~BaseThread()
{
	Stop();
}

unsigned int BaseThread::Start()
{
	return pthread_create(&mPid, NULL, Run, this);
}

void BaseThread::Stop()
{
	if (mPid < 0) {
		return;
	}
	//kill thread
	pthread_join(mPid, NULL);
}

unsigned int BaseThread::GetPid()
{
	return mPid;
}
