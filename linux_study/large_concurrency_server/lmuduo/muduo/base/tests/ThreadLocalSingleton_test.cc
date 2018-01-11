#include <muduo/base/ThreadLocalSingleton.h>
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Thread.h>

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <stdio.h>

class Test : boost::noncopyable
{
 public:
  Test()
  {
    printf("tid=%d, constructing %p\n", muduo::CurrentThread::tid(), this);
  }

  ~Test()
  {
    printf("tid=%d, destructing %p %s\n", 
			muduo::CurrentThread::tid(), this, name_.c_str());
  }

  const std::string& name() const { return name_; }
  void setName(const std::string& n) { name_ = n; }

 private:
  std::string name_;
};

void threadFunc(const char* changeTo)
{
  printf("tid=%d, %p name=%s\n",
         muduo::CurrentThread::tid(),
         &muduo::ThreadLocalSingleton<Test>::instance(),
         muduo::ThreadLocalSingleton<Test>::instance().name().c_str());

  muduo::ThreadLocalSingleton<Test>::instance().setName(changeTo);

  printf("tid=%d, %p name=%s\n",
         muduo::CurrentThread::tid(),
         &muduo::ThreadLocalSingleton<Test>::instance(),
         muduo::ThreadLocalSingleton<Test>::instance().name().c_str());

  // no need to manually delete it
  // muduo::ThreadLocalSingleton<Test>::destroy();
}

int main()
{
  muduo::ThreadLocalSingleton<Test>::instance().setName("main one");
  muduo::Thread t1(boost::bind(threadFunc, "thread1"));
  muduo::Thread t2(boost::bind(threadFunc, "thread2"));
  t1.start();
  // name ""
  // name thread1
  t2.start();
  // name ""
  // name thread2
  t1.join();
  printf("tid=%d, %p name=%s\n",
         muduo::CurrentThread::tid(),
         &muduo::ThreadLocalSingleton<Test>::instance(),
         muduo::ThreadLocalSingleton<Test>::instance().name().c_str());
  // name main one
  t2.join();

  pthread_exit(0);
  // result:

  // tid=8851, constructing 0x9954028
  // tid=8853, constructing 0xb6300468
  // tid=8853, 0xb6300468 name=
  // tid=8853, 0xb6300468 name=thread2
  // tid=8853, destructing 0xb6300468 thread2
  // tid=8852, constructing 0xb6300468
  // tid=8852, 0xb6300468 name=
  // tid=8852, 0xb6300468 name=thread1
  // tid=8852, destructing 0xb6300468 thread1
  // tid=8851, 0x9954028 name=main one
  // tid=8851, destructing 0x9954028 main one
}
