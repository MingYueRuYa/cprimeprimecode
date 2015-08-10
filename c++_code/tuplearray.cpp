/**
 *  多元数组 tuple
 */ 
#include <iostream>
#include <typeinfo>
#include <map>

int main()
{
	int num = 10;
	double doublenum = 20.0;
	char ch = 'A';
	char *str = "hello tuple";
	//必须是个静态数组
	std::tuple<int, double, char, const char *> mytuple(num, doublenum, ch, str);
	//const int num = 3;
	//下标只能是常量
	auto data0 = std::get<0>(mytuple);
	auto data1 = std::get<1>(mytuple);
	auto data2 = std::get<2>(mytuple);
	auto data3 = std::get<3>(mytuple);

	std::cout << typeid(num).name() << std::endl;
	decltype(data0) dataA; //获取data0数据类型 再次创建
	std::cout << data0 << " " << data1 << " "<< data2 << " "<< data3 << " ";
	return 0;
}
