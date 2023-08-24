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
#include "thread_semphore.hpp"
#include "thread_pool.hpp"

#include <Windows.h>

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

	// TestFuture();
	// TestAsync();

    /*
    thread *t1 = new thread([] () { 

        std::chrono::seconds sleepDuration(10);

        std::this_thread::sleep_for(sleepDuration); 
    });

    
    ::TerminateThread(t1->native_handle(), 0);
	system("pause");
    */

    // mutex test_mutex;

    // unique_lock<mutex> lock(test_mutex);

    // bool owns = lock.owns_lock();

    // lock.unlock();

    // owns = lock.owns_lock();
    // if (owns) {
    //     lock.unlock();
    // }


    // Thread::test_thread_seamphore();
    
    // ThreadPool::test_any();

    ThreadPool::test_thread_pool();

    getchar();

	return 0;
}
