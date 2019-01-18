/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef thread_get_retvalue_h
#define thread_get_retvalue_h

#include <mutex>
#include <thread>
#include <future>
#include <utility>
#include <vector>
#include <iostream>

int func_future(int x) { return x + 2; }

void TestFuture()
{
	std::packaged_task<int(int)> task(func_future);
	std::future<int> fut = task.get_future();
	std::thread(std::move(task), 2).detach();

	int value = fut.get();
	std::cout << "The result is " << value << std::endl;
	
	std::vector<std::shared_future<int>> vc_share_future;
	std::shared_future<int> sf = std::async(std::launch::async, 
		[](int a, int b) { return a + b; }, 2, 3);

	vc_share_future.push_back(sf);
	std::cout << "The shared_future result is " << vc_share_future[0].get() <<
	std::endl;
}

void TestAsync()
{
	std::future<int> f1 = std::async(std::launch::async, []() { return 8; });
	std::cout << "f1 " << f1.get() << std::endl;

	std::future<void> f2 = std::async(std::launch::async, []() {
		std::cout << 8 << endl;
		return;
	});

	f2.wait();

	std::future<int> f3 = std::async(std::launch::async, []() {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
	});

	std::cout << "waiting...\n";
	std::future_status status;
	do {
		status = f3.wait_for(std::chrono::seconds(1));
		
		if (status == std::future_status::deferred) {
			std::cout << "deferred...\n";
		} else if (status == std::future_status::ready) {
			std::cout << "ready...\n";
		} else if (status == std::future_status::timeout) {
			std::cout << "timeout...\n";
		}
	} while(status != std::future_status::ready);

	std::cout << "result is " << f3.get() << std::endl;

}

#endif // thread_get_retvalue_h
