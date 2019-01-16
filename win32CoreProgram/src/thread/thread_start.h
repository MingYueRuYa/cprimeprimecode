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
#include <string>
#include <vector>
#include <list>
#include <memory>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::list;

std::mutex g_lock;

void func()
{
	g_lock.lock();
	
	std::cout << "enterd thread:" << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "leaving thread:" << std::this_thread::get_id() << std::endl;

	g_lock.unlock();
}

void func_parameter(int index, const string &name)
{
	std::cout << "enterd thread:" << std::this_thread::get_id() << std::endl;
	std::cout << "index " << index << " name " << name;
	std::this_thread::sleep_for(std::chrono::seconds(20));
	std::cout << "leaving thread:" << std::this_thread::get_id() << std::endl;
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

void thread_deatch(int index, const string &name)
{
	std::thread t1(func_parameter, index, name);
	// detach之后，主线程退出，就算这个detach线程没有执行结束也不会出错
	t1.detach();
}

void thread_move()
{
	std::thread t1(func);
	std::thread t2(std::move(t1));
	// move之后不在t1.join() 否则会爆出异常
	// t1.join();
	t2.join();
}

void thread_bind()
{
	std::thread t1(std::bind(func_parameter, 1, "linux"));
	t1.join();
}

void thread_lambda()
{
	std::thread t1([](int index, const string &name) {
		std::cout << "enterd thread:" << std::this_thread::get_id() << std::endl;
		std::cout << "index " << index << " name " << name;
		std::this_thread::sleep_for(std::chrono::seconds(20));
		std::cout << "leaving thread:" << std::this_thread::get_id() << std::endl;
	}, 5, "unix");
	t1.join();
}

void thread_copy()
{
	std::thread t(func);
	std::thread t1(func);

	vector<std::thread> vcthread;
	vcthread.push_back(std::move(t));
	vcthread.push_back(std::move(t1));

	list<std::shared_ptr<std::thread>> listthread;
	listthread.push_back(std::make_shared<std::thread>(func));

	for (auto &t : vcthread) {
		t.join();
	}

	for (auto &t : vcthread) {
		if (t.joinable()) { cout << "thread is joinable" << endl; }
		else { cout << "thread not joinable" << endl; }
	}

	for (auto &t : listthread) {
		t->join();
	}
}

#endif // thread_start_h