/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef threadpool_h
#define threadpool_h

#include "syncqueue.hpp"

#include <list>
#include <memory>
#include <thread>
#include <atomic>
#include <functional>

using std::list;
using std::thread;
using std::atomic;
using std::function;
using std::shared_ptr;

namespace XIBAO
{
class ThreadPool
{
    using Task = function<void ()>;

public:
    explicit ThreadPool(int maxTaskCount = 5, int numThreads = std::thread::hardware_concurrency()) 
        : mQueue(maxTaskCount)
    {
        // Start(numThreads); 
        mNumThreads = numThreads;
    }

    ~ThreadPool()
    {
        Stop();
    }

    void Stop()
    {
        std::call_once(mFlag, [this] () { StopThreadGroup(); });
    }

    void AddTask(Task &&task)
    {
        mQueue.Put(std::forward<Task>(task));
    }

    void AddTask(Task &task)
    {
        mQueue.Put(task);
    }

    void Start()
    {
        mRunning = true;

        for (int i = 0; i < mNumThreads; ++i) {
            mThreadList.push_back(std::make_shared<thread>(&ThreadPool::RunInThread, this));
        }
    }

private:
    void RunInThread()
    {
        while (mRunning) {
            list<Task> task_list;
            mQueue.Take(task_list);

            for (auto &task : task_list) {
                if (! mRunning) { return; }

                task();
            }
        }
    }

    void StopThreadGroup()
    {
        mQueue.Stop();
        mRunning = false;

        for (auto join_thread : mThreadList) {
            if (nullptr != join_thread) { join_thread->join(); }
        }
        
        mThreadList.clear();
    }

private:
    int mNumThreads;
    std::once_flag mFlag;
    atomic<bool> mRunning;
    SyncQueue<Task> mQueue; 
    list<shared_ptr<thread>> mThreadList; 
};

}

#endif // threadpool_h
