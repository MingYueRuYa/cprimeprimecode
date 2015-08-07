#include <iostream>

//通用可变参数模板  处理不限定的参数，处理不同类型

//空函数，接口，最后结束递归, 新版本编译，这是个坑切记
void showall()
{

}

template<typename T, typename...Args>
void showall(const T &value, const Args &...args)
{
	std::cout << value << std::endl;
	showall(args...);
}


//T ＆vlaue，Args &...args ---> 可以修改原来的数据
//T value , Args ...args --->只可以修改副本的数据
//const T value , const Args ...args --->不可以修改副本，不可以修改原数据
//const T ＆value，const Args ＆...args ---> 引用数据不可以修改
int main(int argc, char *argv[])
{
	int num1 = 10, num2 = 9, num3 = 11;
	double db1 = 10.8, db2 = 10.9;
	char str[40] = "linux";
	showall(num1);
	std::cout << "\n\n\n";
	return 0;
}
