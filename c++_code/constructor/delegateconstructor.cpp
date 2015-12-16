/*
 * 委托构造函数
 * */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class A
{
public:
  A()
  {
	age = 0;
	name = "linux";
	cout << "A() " << endl;
  }
	
  //A(int pAge) 委托为A()无参构造函数进行构造，所以A()先执行，在执行A(int pAge)
  //注意：
  //1.不能写成A(int pAge) : A() , age(pAge) 这就是说委托构造函数不能再使用初始化列表初始化其他成员。
  //2.不能写成递归委托，否则会出现段错误现象。
  A(int pAge) : A()
  {
	cout << "A(int pAge)" << endl;
  }

  void show() const
  {
	cout << age << " " << name << endl;
  }
private:
  int age;
  char *name;

};


int main(int argc, char *argv[])
{
  A a(10);
  a.show();
  return 0;
}
