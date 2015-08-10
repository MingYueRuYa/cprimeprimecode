/*
 * using 别名
 * */
#include <iostream>

namespace space //隔离模板，避免冲突
{
	template<class T>	using ptr = T*; //模板的简写
}


int add(int a, int b)
{
	return a+b;
}

typedef int(*padd)(int a, int b);
using FUN = int (*)(int a, int b); //利用using起别名
int main()
{
	padd p = add;
	std::cout << p(1, 2) << std::endl;
	FUN fun = add;
	std::cout << p(2, 2) << std::endl;

	space::ptr<int> pint(new int(5));
	std::cout << *pint << std::endl;
	return 0;
}
