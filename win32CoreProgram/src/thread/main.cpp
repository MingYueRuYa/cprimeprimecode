/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "thread_start.h"
#include "thread_mutex.h"
#include "SyncQueue.hpp"

int main(int argc, char **argv)
{
	
	// thread_start();
	// thread_deatch(1, "liushixiong");
	// thread_move();
	// thread_bind();
	// thread_copy();

	// TestMutex();
	// TestRecursiveMutex();
	// TestTimeoutMutex();

	TestSyncQueue();

	system("pause");

	return 0;
}
