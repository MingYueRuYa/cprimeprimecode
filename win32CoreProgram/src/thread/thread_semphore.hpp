/****************************************************************************
**
** Copyright (C) 2023 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

/*!
* 1、利用condition_variable 和mutex 模拟 Seamphore
* 2、Seamphore 与 mutex 最大的区别就是：
*   Seamphore 可以跨线程使用
*   Seamphore可以看作资源无限制的mutex
*/

#include <mutex>
#include <memory>
#include <condition_variable>
#include <iostream>
#include <thread>

namespace Thread
{
class Seamphore
{
public:
    explicit Seamphore(int limit = 0)
        : resLimit_(limit)
    {
    }
    ~Seamphore() = default;

    // 获取一个资源
    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        // 等待信号有资源。没有资源，会堵塞当前线程
        cond_.wait(lock, [&] ()->bool { return resLimit_ > 0; });
        resLimit_--;
    }

    // 增加一个信号量
    void post()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        ++resLimit_;
        cond_.notify_all();
    }

private:
    uint32_t resLimit_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

Seamphore sem(1);

void thread_func_1()
{
    sem.wait();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "first, I am in..." << std::this_thread::get_id() << std::endl;
    sem.post();
}

void thread_func_2()
{
    sem.wait();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "second, I am in..." << std::this_thread::get_id() << std::endl;
    sem.post();
}

void test_thread_seamphore()
{
    std::thread thread(thread_func_1);
    std::thread thread_1(thread_func_2);
    thread.detach();
    thread_1.detach();
}

}