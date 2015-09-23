/*
 *	类型转换函数，将复杂类型转换为基本类型
 *	类型转换函数格式，没有返回值，方式return T，没有参数 \
 *		只能是成员函数
 *	operator T() {
 *		//TODO SOMETHING	
 *		return A;
 *	}
 *
 * */
#include <iostream>

class A
{			
public:
	int a1;
	int a2;
	void Print() {
		std::cout << "a1 = " << a1 << "  a2 = " << a2 << std::endl;
	}
};

class Complex
{
public:
	Complex();
	Complex(int num);
	Complex(int real, int virtualnum);
	operator int();
	operator A();
private:
	int real;
	int virtualnum;
};

Complex::Complex() {
	real = 0;
	virtualnum = 0;
}

Complex::Complex(int num) {
	real = num;
	virtualnum = num;
}

Complex::Complex(int real, int virtualnum) {
	this->real = real;
	this->virtualnum = virtualnum;
}

Complex::operator int() {
	return real;
}

Complex::operator A() {
	A a;
	a.a1 = this->real;
	a.a2 = this->virtualnum;
	return a;
}

int main()
{
	Complex com(1, 2);
	Complex com01 = 1;
	int num = com;
	std::cout << num << std::endl;
	A a = (A)com; //等价于 A a = com;
	a.Print();
	return 0;
}

