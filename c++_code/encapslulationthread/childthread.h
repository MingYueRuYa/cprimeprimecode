/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef childthread_h
#define childthread_h

#include "basethread.h"

class ChildThread : public BaseThread
{
public:
	ChildThread();

	~ChildThread();

protected:
	virtual void Execute();

};

#endif //childthread_h
