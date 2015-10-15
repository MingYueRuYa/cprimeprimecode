/*
 * c和c++函数指针
 * c++中的类成员函数指针数组
 * */
//#define CFUNCPOINTER
#ifdef CFUNCPOINTER
#include <stdio.h>
#else
#include <iostream>
#include <typeinfo>

class com
{
private:
	int a;
	int b;
public:
	com(int x, int y) : a(x), b(y)
	{}
	int add(int a, int b)
	{
		return a + b;
	}
	int sub(int a, int b)
	{
		return a - b;
	}
	 
	int mul(int a, int b)
	{
		return a * b;
	}

	int div(int a, int b)
	{
		return a / b;
	}


};
int addC(int a, int b)
{
	return a + b;
}

void run()
{
	printf("run\n");
}

#endif

int main()
{
#ifdef CFUNCPOINTER	
	int (*padd)(int, int) = addC;
	void (*prun)(void) = run;
	printf("%d\n", padd(1, 2));
	//*p编译器自动将*p解释为p
	printf("%d\n", (*padd)(1, 2));
	//不管前面都多少的*，编译器都会自动解释为p
	printf("%d\n", (*********padd)(1, 2));
	//& 没有*不可以执行的，超过两个地址也不可以
	printf("%d\n", (&(**padd))(1, 2));
	//&p不能
	//printf("%d\n", &padd(1, 2));
	//padd和*padd的地址是一样的
	printf("%p, %p, %p", &padd, padd, *padd);	
	//取地址，取就是cpu即将调用函数执行c语言内嵌ASM
	//一些老版本的编译器，&padd和padd, *padd是同样的效果
	prun();
#else
#define COM1
#ifdef COM1 
	int (*padd)(int, int) = addC;
	//只能有一个取地址符号，*多少无所谓和c是一样的
	std::cout << (**************&padd)(10, 20) << "\n";
	com com1(100, 20);
	//auto会自动判断类型，这个函数指针中隐藏了一个参数_thiscall表示当前class
	//所以下面声明函数指针的时候，要加上com::表示函数指针的类型
	auto pfun = &com::add;
	int (com::*pfun01) (int, int) = &com::sub;
	//指定com实例化对象调用函数指针
	std::cout << (com1.*pfun)(10, 20) << std::endl;
	std::cout << (com1.*pfun01)(10, 20) << std::endl;
	std::cout << typeid(pfun).name() << std::endl;
	std::cout << typeid(pfun01).name() << std::endl;
#else
	typedef int (com::*pfun)(int, int);
	com com2(100, 20);
	//指向类成员函数指针数组
	//pfun pfunarray[4] = {&com::add, &com::sub, &com::mul, &com::div};
	int (com::*pfunarray[])(int, int) = {&com::add, &com::sub, &com::mul, &com::div};
	for (int i = 0; i < 4; i++) {
		std::cout << (com2.*pfunarray[i])(10, 20) << std::endl;
	}
	//指向类成员函数指针的指针
	int (com::**ppfunc)(int, int) = pfunarray;
	for (; ppfunc < pfunarray + 4; ppfunc++) {
		std::cout << (com2.**ppfunc)(10, 20) << "\n";
	}
#endif

#endif
	return 0;
}



