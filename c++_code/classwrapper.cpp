/*
 * 类包装器
 * */
#include <iostream>

template<typename T, typename F>
T run(T t, F f)
{
	return f(t);	
}

class Mul
{
public:
	int number;
	Mul(int num) : number(num)
	{}

	int operator()(int num)
	{
		return num * number;	
	}
};



int add(int num)
{
	return num + 10;
}

int main()
{
	int num = 101;
	Mul mul(11);
	std::cout << run(num, mul) << std::endl;
	std::cout << run(num,Mul(101)) << std::endl;
	return 0;
}

int main01()
{
	auto num = 100;
	auto func = add;//int (*pfunc) = add;
	int (*pfunc)(int num) = add;
	std::cout << run(num, add) << std::endl;
	std::cout << func(1010) << std::endl;
	std::cout << pfunc(101) << std::endl;

	return 0;
}
