//函数模板选择问题

#include <iostream>

//函数模板可以对类型进行优化重载，根据类型会覆盖
//如果仍然需要使用模板函数，需要实例化
template<typename T>
T add(T a, T b)
{
	std::cout << "T add" << std::endl;
	return a + b;
}

//普通函数
int add(int a, int b)
{
	std::cout << "int add" << std::endl;
	return a + b;
}

int main()
{
	int a = 10, b = 20;
	double ab = 10.0, ac = 20.0;
	add(ab, ac);
	add(a, b);
	add<int>(a, b);
	return 0;
}
