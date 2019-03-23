/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "thread_start.h"
#include "thread_mutex.h"
#include "SyncQueue.hpp"
#include "counter.hpp"
#include "thread_get_retvalue.h"

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

	// TestSyncQueue();

	// TestMutexCounter();
	// TestAtomicCounter();

	TestFuture();
	// TestAsync();

	system("pause");

	return 0;
}
