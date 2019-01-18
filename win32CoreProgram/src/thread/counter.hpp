/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef counter_h
#define counter_h

#include <mutex>
#include <thread>
#include <iostream>
#include <atomic>

using std::cout;
using std::endl;
using std::mutex;
using std::lock_guard;

struct Counter {
public:
	Counter() :mCount(0) {}

	int Increment()
	{
		lock_guard<mutex> lock(mMutex);
		++mCount;
		return mCount;
	}

	int Decrement()
	{
		lock_guard<mutex> lock(mMutex);
		--mCount;
		return mCount;
	}

	int GetValue()
	{
		return mCount;
	}

private:
	int mCount;
	mutex mMutex;
};

struct AtomicCounter {
	AtomicCounter() : count(0) {}

	void Increment()
	{
		++count;
	}

	void Decrement()
	{
		--count;
	}

	int get()
	{
		return count;
	}

private:
	std::atomic<int> count;
};

struct Counter g_counter;

void test_increment()
{
	for (int i = 0; i < 20; ++i) {
		cout << g_counter.Increment() << endl;
	}
}

void test_decrement()
{
	for (int i = 0; i < 20; ++i) {
		cout << g_counter.Decrement() << endl;
	}
}

void TestMutexCounter()
{
	thread t1(test_increment);
	thread t2(test_decrement);
	
	t1.join();
	t2.join();
}

struct AtomicCounter g_atomic_counter;

void test_increment1()
{
	for (int i = 0; i < 20; ++i) {
		g_atomic_counter.Increment();
		cout << "inc " << g_atomic_counter.get() << endl;
	}
}

void test_decrement1()
{
	for (int i = 0; i < 20; ++i) {
		g_atomic_counter.Decrement();
		cout << "dec " << g_atomic_counter.get() << endl;
	}
}

void TestAtomicCounter()
{
	thread t1(test_increment1);
	thread t2(test_decrement1);
	
	t1.join();
	t2.join();
}

#endif // counter_h