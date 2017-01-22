/****************************************************************
 **
 ** Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

//子类与父类的之间赋值情况，A为父类，B为子类
//1.实例之间的赋值
// A a = B() ----> 没有编译错误，先构造父类，在构造子类，还会有个拷贝构造的过程。中间调用的虚函数还是子类实现的。
// B b = A() ----> 有编译错误，类型不匹配
//
//2.指针之间的赋值
// A *a = new B() ----> 多态的基础，直接操作的是地址
// B *b = new A() ----> 可以的操作，但是个危险的操作，子类操作的成员，一旦超过父类的地址空间，就会出现异常情况
//
//3.引用之间的赋值
//B b;
//A &a = b ----> 与实例之间的赋值类似，只是没有拷贝构造的过程。
//B &b = A()  ----> 编译错误，即使做强制转换还是错误

#include <iostream>
#include <string>

using namespace std;

class Parent
{
public:
	Parent()
	{
		mName = "Parent";
		cout << "Parent ctor..." << endl;
	}

	~Parent()
	{
		cout << "Parent dtor..." << endl;
	}

	Parent(const Parent &pParent)
	{
		mPid = pParent.mPid;
		mName = pParent.mName;
		cout << "Copyctor..." << endl;
	}

	virtual void GetName()
	{
		cout << mName << endl;
	}

protected:
	int mPid;

	string mName;

};

class Child : public Parent
{
public:
	Child()
	{
		mName = "Child";
		cout << "Child ctor..." << endl;
	}

	~Child()
	{
		cout << "Child dtor..." << endl;
	}

public:
	int Age = 0;

};

int main(int argc, char *argv[])
{
//  Parent p = Child();
//	p.GetName();

//	Child c = static_cast<Child>(Parent()); //error 利用强制转换也会发生编译错误

//	Child *d = static_cast<Child *>(new Parent());  //未定义的行为，危险行为
//	cout << d->Age << endl;

//	Child c;
//	Parent &p = c;
//	p.GetName();

	Parent p;
	Child &c = static_cast<Child>(p);

	return 0;
}

