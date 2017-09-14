/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#ifndef thread_h
#define thread_h

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;

namespace use_thread
{

static void func(int a1, int a2, int a3)
{
    cout << "a1=" <<a1 << ", a2=" << a2 << ", a3=" << a3 << endl;
}

static void Continuefunc(int a1, int a2, int a3)
{
    //while (1) {
        cout << "a1=" <<a1 << ", a2=" << a2 << ", a3=" << a3 << endl;
    //}
}

static void test_useage_thread()
{
    cout << "----------------basic useage thread--------------------" << endl;
    thread t1(func, 1, 2, 3);
    //获取t1线程ID
    cout << "get t1 thread id=" << std::hex << t1.get_id() << endl;
    //join函数会阻塞线程
    t1.join(); 

    thread t2(Continuefunc, 1, 2, 3);
    cout << "get t2 thread id=" << std::hex << t2.get_id() << endl;
    //后台执行t2de线程函数，并且不会因为main函数结束，线程函数未执行完而产生异常，在vs2013下测试线程函数没有执行玩main函数不能退出
    t2.detach();

    cout << "after t2, main is runing" << endl;

    //以lambda表达式作为被绑定的线程函数
    thread t4([](int a, int b, int c) {
        //线程休眠5S
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cout << "a=" << a << ", b=" << b << ", c=" << c << endl;
    }, 4, 5, 6);
    t4.join();
    
    //获取CPU和核数
    cout << "cpu kernel number:" << thread::hardware_concurrency() << endl;

    //当添加下面的这条注释语句，就会爆出异常。因为线程对象先于线程函数结束了。要确保线程对象的生命周期比线程函数长
    //thread t3(func, 7, 8, 9);
    cout << "----------------basic useage thread--------------------" << endl;
}

static std::mutex g_lock;

static void lock_thread() //mutex互斥锁机制
{
    g_lock.lock();
    
    static int number = 0;
    cout << "in id:" << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "number=" << ++number << endl;

    g_lock.unlock();
}

static void lock_guard_thread()
{
    std::lock_guard<std::mutex> lock(g_lock);
    
    static int number = 0;
    cout << "in id:" << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "number=" << ++number << endl;
}

static std::timed_mutex time_mutex;

static void time_mutex_thread()
{
    //设置超时锁
    std::chrono::milliseconds timeout(3000);

    while (true) {
        //带超时的锁，当阻塞超过100ms时就返回false
        if (time_mutex.try_lock_for(timeout)) {
            cout << std::this_thread::get_id() << ": do work with the mutex." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        } else {
            cout << std::this_thread::get_id() << ": do work without the mutex." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    } //while
}

static void synchronize_thread()
{
    cout << "----------------synchronisze thread--------------------" << endl;

    cout << "----------------test mutex--------------------" << endl;
    thread t1(lock_thread);
    thread t2(lock_thread);
    thread t3(lock_thread);

    t1.join();
    t2.join();
    t3.join();
    cout << "----------------test mutex--------------------" << endl;

    cout << "----------test lock guard mutex---------------" << endl;
    thread t4(lock_guard_thread);
    thread t5(lock_guard_thread);
    thread t6(lock_guard_thread);

    t4.join();
    t5.join();
    t6.join();
    cout << "----------test lock guard mutex---------------" << endl;

    cout << "-------------test time mutex------------------" << endl;
    thread t7(time_mutex_thread);
    //thread t8(time_mutex_thread);
    t7.join();
    //t8.join();
    cout << "-------------test time mutex------------------" << endl;

    cout << "----------------synchronisze thread--------------------" << endl;
}

static void test_thread()
{
    cout << "**********************test thread**********************" << endl;
    //test_useage_thread();
    synchronize_thread();
    cout << "**********************test thread**********************" << endl;
}

};

#endif //thread_h