/*
 * 模板引用  std:ref 不是std number function
 * */
#include <iostream>
using namespace std;
	template<class T>
void com(T arg)
{
	std::cout << "com = " << &arg << "\n";
	arg++;
}

template<class T>
void com01(T &arg)
{
	std::cout << "com = " << &arg << "\n";
	arg++;
}

int main()
{
	int count = 10;	
	//不能修改count的值
	com(count);
	std::cout << count << "\n"; 
	//传递引用也不能修改count值
	int &ccount = count;
	com(count);
	std::cout << count << "\n"; 

	//模板引用
	com01(count);		
	std::cout << count << "\n"; 

	com(std::ref(count));
	std::cout << count << "\n";
	return 0;
}

