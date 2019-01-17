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

void TestMutex()
{
	struct Complex complex;
	complex.both(3, 4);
}

#endif // thred_mutex
