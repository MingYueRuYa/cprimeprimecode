/*
 *	纯虚函数--->就是抽象类
 * */
#include <iostream>

class Base
{
public:
	virtual void showname() = 0;
	virtual void showaddr() = 0;
	virtual void showage() = 0;
};

class GreatFather: public Base
{
public:
	//这里要定义虚函数，不能声明虚函数，虽然没有具体的实现
	virtual void Hi() {
		std::cout << "GreatFather hi" << std::endl;
	}

	void showname() {
		std::cout << "this is GreatFather." << std::endl;
	}

	void showaddr() {
		std::cout << "Shanghai PuDong." << std::endl;
	}

	void showage() {
		std::cout << "I am 23." << std::endl;
	}

};

class Father: public GreatFather//: public Base
{
public:
	void showname() {
		std::cout << "this is father." << std::endl;
	}

	void Hi() {
		std::cout << "father hi" << std::endl;
	}	

};

int main()
{
	//x64平台下指针为8个字节，在x86平台下为4个字节，不管有个多少虚函数，都是一个指针指向虚函数表
	std::cout << sizeof(Base) << std::endl;
}

int main01()
{
	//拥有纯虚函数的类不能实例化
	//Base base;		
	//继承Base类，只要有一个纯虚函数没有实现，就还是抽象类
	GreatFather greatfather;
	Father father;
	father.showname();
	father.Hi();
	//调用父类的方法
	father.GreatFather::Hi();
	//father.showname();
	return 0;
}
