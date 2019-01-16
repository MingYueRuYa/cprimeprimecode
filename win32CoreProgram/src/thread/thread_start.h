/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef thread_start_h
#define thread_start_h

#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

std::mutex g_lock;

void func()
{
	g_lock.lock();
	
	std::cout << "enterd thread:" << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "leaving thread:" << std::this_thread::get_id() << std::endl;

	g_lock.unlock();
}

void thread_start()
{
	std::thread t1(func);
	std::thread t2(func);
	std::thread t3(func);

	t1.join();
	t2.join();
	t3.join();

}

#endif // thread_start_h