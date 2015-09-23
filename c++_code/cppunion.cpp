/*
 *  c++ 的联合体
 * */

#include <iostream>

/*
 *	union 的本质也是个类，可以有内部函数
 *	内部数据是共享的，不同对象之间是独立的，函数代码也是共享
 *	具备结构体的所有功能，不能实现继承
 * */

union MyUnion
{
	int num;
	double db;
	void go()
	{}
};

union MyUnionA
{
	int num;
	double db;
	void go()
	{}
};


int main()
{

	//大小为8
	std::cout << sizeof(MyUnion) << std::endl;
	MyUnion A;
	A.num = 10;
	std::cout << A.num << std::endl;
	//打印db时出现乱码现象，是因为把int类型当做double解析
	std::cout << A.db << std::endl;

	
	return 0;
}
