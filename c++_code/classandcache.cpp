/*
 *	类中的成员于内存的关系
 * */

#include <iostream>

/*
 *	类中代码都是放在代码区（包括静态成员），普通成员变量都是于具体的对象关联
 *
 * */
class MyClass
{
public:
	static void staticfun();
	void commonfun();
};

void MyClass::staticfun()
{
	std::cout << "myclass staticfun" << std::endl;
}

void MyClass::commonfun()
{
	std::cout << "myclass commonfun" << std::endl;
}

class MyClassB
{
public:
	MyClassB(int num, int &myint):num(num), mynum(myint)
	{
		const int *pint = &num;
		int *pnum = const_cast<int *>(pint);
		//类中const属性可以去掉，但是外部就不行
		*pnum = 12;
		std::cout << num << std::endl;
	}
	//const构造时初始化或者使用默认值
	const int num;
	//构造时初始化
	int &mynum;
	//可以不初始化
	static int staticnum;
	//可以不初始化
	const static int staticconstnum;
	//也可以不初始化---->主要包含static就可以不初始化
	static const int conststaticnum;
};
int MyClassB::staticnum = 1;
//只要包含const在初始化的时候就要加上const属性，而static则不需要加上的
const int MyClassB::staticconstnum = 2;
const int MyClassB::conststaticnum = 3;
	
int main()
{
	MyClass::staticfun();
	MyClass myclass;
	//利用函数指针指向类中的静态函数，于具体的对象没有关系
	void (*pfunc)() = &MyClass::staticfun;
	pfunc();
	//利用函数指针指向类中的普通函数	
	void (MyClass::*pcommonfunc)() = &MyClass::commonfun;
	//注意()优先级高于*,要指定调用的对象。
	(myclass.*pcommonfunc)();	

	int num = 10;
	MyClassB classb(0,num);
	//静态常量区只读不能写，但是静态去可读可写
	const int *pstaticnum = &(MyClassB::conststaticnum);
	int *pnum = const_cast<int *>(pstaticnum);
	*pnum = 13;
	std::cout << MyClassB::staticnum << std::endl;
	return 0;
}
