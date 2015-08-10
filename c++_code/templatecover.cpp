/*
 *函数模板覆盖
 * */
#include <iostream>
struct info
{
	char name[40];
	double db;
	int data;
};

template<typename T>
void swap(T &a, T &b)
{
	std::cout << "通用函数模板" << std::endl;
	T temp = a;
	a = b;
	b = temp;
}

//模板为空，明确参数类型，覆盖函数 模板的类型
void swap(info &info01, info &info02)
{
	std::cout << "特有函数模板" << std::endl;
	//通用模板可以实现通用，针对自己的数据类型做出优化
	info tmp = info01;
	info01 = info02;
	info02 = tmp;
}

//通过对通用函数的指定实例化swap<info> ，同样可以调用通用函数
//实例化调用 swap<T>
int main02()
{
	info info01 = {"linux", 20.9, 10};
	info info02 = {"unix", 30.9, 30};
	swap<info>(info01, info02);
	std::cout << info01.name << " " << info01.db << " " << info01.data <<std::endl;
	std::cout << info02.name << " " << info02.db << " " << info02.data <<std::endl;
	return 0;
}
//调用特有函数模板
int main01()
{
	info info01 = {"linux", 20.9, 10};
	info info02 = {"unix", 30.9, 30};
	swap(info01, info02);
	std::cout << info01.name << " " << info01.db << " " << info01.data <<std::endl;
	std::cout << info02.name << " " << info02.db << " " << info02.data <<std::endl;
	return 0;
}
