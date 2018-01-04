#include <muduo/base/Exception.h>
#include <stdio.h>

class Bar
{
 public:
  void test()
  {
    throw muduo::Exception("oops");
  }
};

// static 有不导出符号的作用
static void foo()
{
  Bar b;
  b.test();
}

int main()
{
  try
  {
    foo();
  }
  catch (const muduo::Exception& ex)
  {
    printf("reason: %s\n", ex.what());
    printf("stack trace: %s\n", ex.stackTrace());
  }
}
