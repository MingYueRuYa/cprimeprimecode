/*
 * 引用内部函数绑定机制
 **/

#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;
//仿函数，创建一个函数指针，引用一个结构体内部的或者一个类内部的共有函数

struct MyStruct
{
	void add(int a)
	{
		cout << a << endl;
	}
	void add01(int a, int b)
	{
		cout << a + b << endl;
	}
	void add02(int a, int b, int c)
	{
		cout << a + b + c << endl;
	}

};

int main()
{
	MyStruct mystruct;
	//创建函数指针，类结构体，数据私有，代码共享
	//函数通过调用，调用需要传递对象名进行区分
	void (MyStruct::*p)(int a) = &MyStruct::add;
	p(1);
	return 0;
}

int main01()
{

	MyStruct mystrcut01;
	//auto自动变量，地址，函数指针bind绑定
	auto func = bind(&MyStruct::add, &mystrcut01, _1); //参数位置
	auto func02 = bind(&MyStruct::add01, &mystrcut01, _1, _2);
	auto func03 = bind(&MyStruct::add02,mystrcut01, _1, _2, _3);
	func(2);
	func02(2, 3);
	func03(2, 3, 4);


	return 0;
}
