#include <muduo/base/ThreadLocal.h>
#include <muduo/base/CurrentThread.h>
#include <muduo/base/Thread.h>

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

muduo::ThreadLocal<Test> testObj1;
muduo::ThreadLocal<Test> testObj2;

void print()
{
  printf("tid=%d, obj1 %p name=%s\n",
         muduo::CurrentThread::tid(),
		 &testObj1.value(),
         testObj1.value().name().c_str());

  printf("tid=%d, obj2 %p name=%s\n",
         muduo::CurrentThread::tid(),
		 &testObj2.value(),
         testObj2.value().name().c_str());
}

void threadFunc()
{
  print();
  testObj1.value().setName("changed 1");
  testObj2.value().setName("changed 42");
  print();
}

int main()
{
  testObj1.value().setName("main one");
  print();
  muduo::Thread t1(threadFunc);
  t1.start();
  t1.join();
  testObj2.value().setName("main two");
  print();
// result:
// tid=7987, constructing 0x9023028
// tid=7987, obj1 0x9023028 name=main one
// tid=7987, constructing 0x9023038
// tid=7987, obj2 0x9023038 name=
// tid=7988, constructing 0xb6b00468
// tid=7988, obj1 0xb6b00468 name=
// tid=7988, constructing 0xb6b00478
// tid=7988, obj2 0xb6b00478 name=
// tid=7988, obj1 0xb6b00468 name=changed 1
// tid=7988, obj2 0xb6b00478 name=changed 42
// tid=7988, destructing 0xb6b00468 changed 1
// tid=7988, destructing 0xb6b00478 changed 42
// tid=7987, obj1 0x9023028 name=main one
// tid=7987, obj2 0x9023038 name=main two
// tid=7987, destructing 0x9023028 main one
// tid=7987, destructing 0x9023038 main two
  pthread_exit(0);
}
