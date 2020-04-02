/****************************************************************************
**
** Copyright (C) 2019 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#ifndef syncqueue_h
#define syncqueue_h

#include "noncopyable.h"

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>

#ifdef _DEBUG
#include <iostream>

using std::cout; 
using std::endl; 
#endif

using std::list;
using std::mutex;
using std::unique_lock;
using std::lock_guard;
using std::condition_variable;

namespace XIBAO
{

/*
    同步队列
*/
template <typename T>
class SyncQueue : public NonCopyable
{
public:
    SyncQueue(int maxSize) : mMaxSize(maxSize), mNeedStop(false)
    {}

    ~SyncQueue() 
    { 
        Stop(); 
    }

    void Put(const T& t)
    {
        Add(t);
    }

    void Put(const T&& t)
    {
        Add(t);
    }
    
    void Take(std::list<T> &listData)
    {
        unique_lock<mutex> locker(mMutex);
        mNotEmpty.wait(locker, [this] () { return mNeedStop || NotEmpty(); });

        if (mNeedStop) { return; }

        listData = std::move(mQueue);
        
        mNotFull.notify_one();
    }

    void Take(T &t)
    {
        unique_lock<mutex> locker(mMutex);
        mNotEmpty.wait(locker, [this] () { return mNeedStop || NotEmpty(); });

        if (mNeedStop) { return; }

        t = mQueue.front();
        mQueue.pop_front();

        mNotFull.notify_one();
    }

    void Stop()
    {
        {
            lock_guard<mutex> guard(mMutex);
            mNeedStop = true;
        }

        mNotFull.notify_all();
        mNotEmpty.notify_all();
    }

    bool Empty()
    {
        lock_guard<mutex> guard(mMutex);
        return mQueue.empty();
    }

    bool Full()
    {
        lock_guard<mutex> guard(mMutex);
        return mQueue.size() == mMaxSize;
    }

    size_t Size()
    {
        lock_guard<mutex> guard(mMutex);
        return mQueue.size();
    }

private:
    bool NotFull() const
    {
#ifdef _DEBUG 
        bool full = mQueue.size() >= mMaxSize;

        if (full) {
            cout << "缓冲区满了，需要等待。。。，异步层的线程ID:" 
                 << std::this_thread::get_id() << endl;
        }

        return ! full;
#else
        return !(mQueue.size() >= mMaxSize);
#endif
    }

    bool NotEmpty() const
    {
#ifdef _DEBUG
        bool empty = mQueue.empty();
        if (empty) {
            cout << "缓冲区空了，需要等待。。。，异步层的线程ID:" 
                 << std::this_thread::get_id() << endl;
        }
        return ! empty;
#else
        return ! mQueue.empty();
#endif

    }

    template <typename F>
    void Add(F &&f)
    {
        unique_lock<mutex> lock(mMutex);
        mNotFull.wait(lock, [this] () { return mNeedStop || NotFull(); });

        if (mNeedStop) { return; }

        mQueue.push_back(std::forward<F>(f));
        mNotEmpty.notify_one();
    }

private:
    list<T> mQueue;
    mutex mMutex;
    condition_variable mNotEmpty;
    condition_variable mNotFull;
    int mMaxSize;
    bool mNeedStop;

};

}

#endif //syncqueue_h
