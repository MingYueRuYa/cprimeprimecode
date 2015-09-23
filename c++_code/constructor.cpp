/*
 *	c++中构造函数
 * */

#include <iostream>

class classA
{
private:
	int a;
	int b;

public:
	classA(int x, int y):a(x), b(y)
	{
//		a = x;
//		b = y;
	}

	void print()
	{
		std::cout << a << " " << b << std::endl;
	}
};

//delete可以禁用默认生成的函数，禁用构造函数无法实例化
//禁用拷贝构造，可以实现禁止别人拷贝你
//default 默认存在
class A
{
public:
	//A()= delete;//默认删除构造函数，无法实例化
	A() = default; //默认存在
	//A(const A &a) = delete; //删除拷贝构造函数
};

int main()
{
	return 0;
}

int main02()
{
	A a;
	A aa(a);
	return 0;
}
int main01()
{
	classA A(10, 20);	
	A.print();
	//编译器提供的是浅拷贝。
	classA B(A);
	B.print();
	
	return 0;
}



