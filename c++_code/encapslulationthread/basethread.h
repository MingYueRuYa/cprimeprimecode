/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef basethread_h

#define basethread_h

#include <pthread.h>

class BaseThread
{
public:
	static void *Run(void *pArg);

public:
	BaseThread();

	virtual ~BaseThread();

	unsigned int Start();

	void Stop();

	unsigned int GetPid();

protected:
	virtual void Execute() = 0;

private:
	pthread_t mPid;

};

#endif //basethread_h


