/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef thread_mutex
#define thred_mutex

#include <iostream>
#include <thread>
#include <mutex>

using std::mutex;
using std::thread;
using std::lock_guard;
using std::recursive_mutex;
using std::timed_mutex;

struct Complex
{
	mutex mMutex;
	int i = 0;
	Complex() : i(0) {}

	void mul(int x)
	{
		lock_guard<mutex> lock(mMutex);
		i *= x;
	}

	void div(int x)
	{
		lock_guard<mutex> lock(mMutex);
		i /= x;
	}

	void both(int x, int y)
	{
		lock_guard<mutex> lock(mMutex);
		mul(x);
		div(y);
	}

};

struct RecursiveComplex
{
	recursive_mutex mMutex;
	int i = 0;
	RecursiveComplex() : i(0) {}

	void mul(int x)
	{
		lock_guard<recursive_mutex> lock(mMutex);
		i *= x;
	}

	void div(int x)
	{
		lock_guard<recursive_mutex> lock(mMutex);
		i /= x;
	}

	void both(int x, int y)
	{
		lock_guard<recursive_mutex> lock(mMutex);
		mul(x);
		div(y);
		std::cout << "recursive both " << std::endl;
	}

};

timed_mutex g_time_mutex;

void work()
{
	std::chrono::seconds timeout(1);
	
	while (true) {
		if (g_time_mutex.try_lock_for(timeout)) {
			cout << std::this_thread::get_id() << " do work with the mutex" 
				 << endl;
			std::chrono::seconds sleepDuration(3);
			std::this_thread::sleep_for(sleepDuration);

			g_time_mutex.unlock();
		} else {
			cout << std::this_thread::get_id() << " do work without the mutex" 
				 << endl;
			std::chrono::seconds sleepDuration(1);
			std::this_thread::sleep_for(sleepDuration);
		}
	}

}

void TestMutex()
{
	struct Complex complex;
	complex.both(3, 4);
}

void TestRecursiveMutex()
{
	struct RecursiveComplex complex;
	//因为同一线程可以多次获取同一互斥量，不会发生死锁
	complex.both(3, 4);
}

void TestTimeoutMutex()
{
	thread t1(work);
	thread t2(work);
	t1.join();
	t2.join();
}

#endif // thred_mutex
