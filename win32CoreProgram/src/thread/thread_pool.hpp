/****************************************************************************
**
** Copyright (C) 2023 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

// 1、如何封装一个any类型
// 2、线程间如何通信
// 3、万能的函数如何封装

#ifndef thread_pool_hpp
#define thread_pool_hpp

#include <mutex>
#include <functional>
#include <queue>
#include <future>
#include <thread>
#include <memory>
#include <chrono>
#include <iostream>
#include <unordered_map>

namespace ThreadPool {
// any类型
class Any {
 public:
  Any() = default;
  ~Any() = default;
  Any(const Any&) = delete;
  Any& operator=(const Any&) = delete;
  /* Any(Any&& any) = default;
   Any& operator=(Any&&) = default;*/

  template <typename T>
  Any(T data) : base_(std::make_unique<Derive<T>>(data)) {}

  template <typename T>
  T cast_() {
    // 注意这里的封装才是点睛之笔
    Derive<T>* pd = dynamic_cast<Derive<T>*>(base_.get());
    if (pd == nullptr) {
      throw "type is unmatch";
    }

    return pd->data_;
  }

 private:
  class Base {
   public:
    virtual ~Base() = default;
  };

  template <typename T>
  class Derive : public Base {
   public:
    Derive(T data) : data_(data) {}
    T data_;
  };

 private:
  std::unique_ptr<Base> base_;
};

void test_any() {
  Any any_1(10);
  int value = any_1.cast_<int>();

  Any any_2(std::string("linux"));
  std::string str = any_2.cast_<std::string>();
}

// 最大任务上限
const int TASK_MAX_THRESHHOLD = 2;
// 最大线程数量上限
const int THREAD_MAX_THRESHHOLD = 1024;
// 空闲时间60s
const int THREAD_MAX_IDLE_TIME = 60;

enum class PoolMode { MODE_FIXED, MODE_CACHED };

// 1、任务如何封装，如何获取返回值
// 2、线程如何退出
// 3、死锁问题
class Thread {
 public:
  using ThreadFunc = std::function<void(int)>;

  Thread(ThreadFunc func) : func_(func), threadId_(generateId_++) {}

  ~Thread() = default;

  void start() {
    std::thread thr(func_, threadId_);
    thr.detach();
  }

  int getId() const { return threadId_; }

 private:
  ThreadFunc func_;
  static int generateId_;
  int threadId_;
};
int Thread::generateId_ = 0;

class ThreadPool {
 public:
  ThreadPool()
      : initThreadSize_(0),
        threadSizeThreshHold_(THREAD_MAX_THRESHHOLD),
        curThreadSize_(0),
        idleThreadSize_(0),
        taskQueMaxThreshHold_(TASK_MAX_THRESHHOLD),
        poolMode_(PoolMode::MODE_FIXED),
        isPoolRuning_(false) {}

  ~ThreadPool() {
    isPoolRuning_ = false;

    // 等待线程池所有的线程返回，两种状态：阻塞 || 正在执行任务
    std::unique_lock<std::mutex> lock(taskQueMtx_);
    notEmpty_.notify_all();
    exitCond_.wait(lock, [&]() -> bool { return threads_.size() == 0; });
  }

  ThreadPool(ThreadPool&&) = delete;
  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  void setMode(PoolMode mode) {
    if (checkRunningState()) {
      return;
    }

    poolMode_ = mode;
  }

  void setTaskQueMaxThreshHold(int taskThreshHold) {
    if (checkRunningState()) {
      return;
    }
    taskQueMaxThreshHold_ = taskThreshHold;
  }

  void setThreadSizeThreshHold(int threshSizeHold) {
    if (checkRunningState()) {
      return;
    }

    if (poolMode_ == PoolMode::MODE_CACHED) {
      threadSizeThreshHold_ = threshSizeHold;
    }
  }

  // 1、可变模板参数
  // 2、引用折叠
  // 3、返回值后置
  // 4、超时返回
  template <typename Func, typename... Args>
  auto submitTask(Func&& func, Args&&... args)
      -> std::future<decltype(func(args...))> {
    // 打包任务，放入到任务队列中
    using RType = decltype(func(args...));
    auto task = std::make_shared<std::packaged_task<RType()>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
    std::future<RType> result = task->get_future();

    // 获取锁
    std::unique_lock<std::mutex> lock(taskQueMtx_);
    // 用户提交任务不能阻塞，最长不能超过1s，否则失败返回
    if (!notFull_.wait_for(lock, std::chrono::seconds(1), [&]() -> bool {
          return taskSize_ < (size_t)taskQueMaxThreshHold_;
        })) {
      // 表示等待1s，任务队列依旧是满的
      std::cerr << "task queue is full, submit task fail" << std::endl;
      // 构造一个空的任务，返回
      auto task = std::make_shared<std::packaged_task<RType()>>(
          []() -> RType { return RType(); });
      // 执行任务
      (*task)();
      return task->get_future();
    }

    // 如果task队列未满, 构成lambda表达式
    taskQue_.emplace([task] { (*task)(); });
    taskSize_++;

    // 通知：任务队列不为空，可以接着生成任务
    notEmpty_.notify_all();

    // cached模式：处理大量小而快的场景，需要根据任务数量和空闲线程数量，判断是否需要再创建线程
    if (poolMode_ == PoolMode::MODE_CACHED && taskSize_ > idleThreadSize_ &&
        curThreadSize_ < threadSizeThreshHold_) {
      std::cout << ">>>> create new thread..." << std::endl;

      // 创建新的线程
      auto ptr = std::make_unique<Thread>(
          std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
      int threadId = ptr->getId();
      threads_.emplace(threadId, std::move(ptr));
      // 启动线程
      threads_[threadId]->start();
      // 修改线程有关数据
      curThreadSize_++;
      idleThreadSize_++;
    }
    return result;
  }

  // 开启线程
  void start(int initThreadSize = std::thread::hardware_concurrency()) {
    // 设置状态
    isPoolRuning_ = true;

    // 记录初始线程个数
    initThreadSize_ = initThreadSize;
    curThreadSize_ = initThreadSize;

    // 创建线程对象
    for (int i = 0; i < initThreadSize_; ++i) {
      auto ptr = std::make_unique<Thread>(
          std::bind(&ThreadPool::threadFunc, this, std::placeholders::_1));
      int threadId = ptr->getId();
      threads_.emplace(threadId, std::move(ptr));
    }

    for (int i = 0; i < initThreadSize_; ++i) {
      // TODO: 这里好像不对
      threads_[i]->start();
      idleThreadSize_++;
    }
  }

  bool checkRunningState() { return isPoolRuning_; }

 private:
  void threadFunc(int threadId) {
    auto lastTime = std::chrono::high_resolution_clock().now();

    for (;;) {
      Task task;
      {
        // 先获取锁
        std::unique_lock<std::mutex> lock(taskQueMtx_);
        std::cout << "tid:" << std::this_thread::get_id() << "尝试获取任务："
                  << std::endl;

        // cached模式下，有可能已经创建了很多的线程。但是空闲时间超过60s，应该把多余的线程结束回收掉
        // 回收条件：1、超过initThreadSize_ 2、空闲时间超过60s
        // 如何判断是超时返回还是执行任务返回？
        while (taskQue_.size() == 0) {
          // 线程池退出
          if (!isPoolRuning_) {
            threads_.erase(threadId);
            std::cout << "threadid:" << std::this_thread::get_id() << " exit"
                      << std::endl;
            exitCond_.notify_all();
            // 线程函数结束
            return;
          }

          if (poolMode_ == PoolMode::MODE_CACHED) {
            if (std::cv_status::timeout ==
                notEmpty_.wait_for(lock, std::chrono::seconds(1))) {
              auto now = std::chrono::high_resolution_clock().now();
              auto dur = std::chrono::duration_cast<std::chrono::seconds>(
                  now - lastTime);
              if (dur.count() >= THREAD_MAX_IDLE_TIME &&
                  curThreadSize_ > initThreadSize_) {
                // 回收当前线程
                threads_.erase(threadId);
                curThreadSize_--;
                idleThreadSize_--;
                std::cout << "threadid:" << std::this_thread::get_id()
                          << " exit" << std::endl;
                return;
              }
            }
          } else {
            notEmpty_.wait(lock);
          }
        }  // while

        idleThreadSize_--;
        std::cout << "tid:" << std::this_thread::get_id() << "获取任务成功"
                  << std::endl;
        // 取出任务
        task = taskQue_.front();
        taskQue_.pop();
        taskSize_--;

        // 如果依然有剩余任务，继续通知其他线程执行任务
        if (taskQue_.size() > 0) {
          notEmpty_.notify_all();
        }

        // 取出一个任务，进行通知，通知可以继续提交生产任务
        notFull_.notify_all();
      }  // 退出当前作用域，就会自动释放锁

      if (task != nullptr) {
        task();
      }

      // 任务已经执行完成
      idleThreadSize_++;
      // 更新线程执行完任务的时间
      lastTime = std::chrono::high_resolution_clock().now();
    }  // for
  }

 private:
  // 线程列表
  std::unordered_map<int, std::unique_ptr<Thread>> threads_;
  // 初始化线程数量
  int initThreadSize_;
  int threadSizeThreshHold_;
  // 当前线程池的线程数量
  std::atomic_int curThreadSize_;
  std::atomic_int idleThreadSize_;

  // Task任务对象
  using Task = std::function<void()>;
  std::queue<Task> taskQue_;
  std::atomic_int taskSize_;
  // 任务队列上限
  int taskQueMaxThreshHold_;

  // 线程同步相关
  std::mutex taskQueMtx_;
  std::condition_variable notFull_;
  std::condition_variable notEmpty_;
  // 资源回收
  std::condition_variable exitCond_;

  PoolMode poolMode_;
  std::atomic_bool isPoolRuning_;
};


int sum1(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    // 比较耗时
    return a + b;
}
int sum2(int a, int b, int c)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return a + b + c;
}

void test_thread_pool()
{
    ThreadPool pool;
    // pool.setMode(PoolMode::MODE_CACHED);
    pool.start(2);

    std::future<int> r1 = pool.submitTask(sum1, 1, 2);
    std::future<int> r2 = pool.submitTask(sum2, 1, 2, 3);
    std::future<int> r3 = pool.submitTask([](int b, int e)->int {
        int sum = 0;
        for (int i = b; i <= e; i++)
            sum += i;
        return sum;
        }, 1, 100);
    std::future<int> r4 = pool.submitTask([](int b, int e)->int {
        int sum = 0;
        for (int i = b; i <= e; i++)
            sum += i;
        return sum;
        }, 1, 100);
    std::future<int> r5 = pool.submitTask([](int b, int e)->int {
        int sum = 0;
        for (int i = b; i <= e; i++)
            sum += i;
        return sum;
        }, 1, 100);
    //future<int> r4 = pool.submitTask(sum1, 1, 2);

    std::cout << r1.get() << std::endl;
    std::cout << r2.get() << std::endl;
    std::cout << r3.get() << std::endl;
    std::cout << r4.get() << std::endl;
    std::cout << r5.get() << std::endl;
}


}  // namespace ThreadPool

#endif // thread_pool_hpp