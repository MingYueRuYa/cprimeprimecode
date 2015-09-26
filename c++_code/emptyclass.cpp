/*
 * 不含任何属性和方法的空类
 * */

#include <iostream>

//空类不含任何属性和方法，但是要注意它含有两个方法，构造和析构函数
class MyClass
{
	public:
		int a;
		virtual void test();
	//	void test1()
	//	{
	//		;	
	//	}
};
int main()
{

	//空类大小 1
	//std::cout << sizeof(MyClass) <<std::endl;
	//添加int a属性 大小为4	
	//std::cout << sizeof(MyClass) <<std::endl;

	//如果再添加方法 大小还是为4，因为方法是共有的，再代码区中
	std::cout << sizeof(MyClass) <<std::endl;

	//但是要注意一旦添加虚方法之后大小变为18，光有一个虚方法大小为8，猜测一个指针大小为8(再x64平台下8,再x86平台下为4)
	
	

	return 0;
}
