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
	BaseThread();

	~BaseThread();

	void Start();

	void Stop();

protected:
	virtual void Run();

};

#endif //basethread_h


