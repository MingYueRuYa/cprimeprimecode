/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

/*
 * 可变的模板参数
 * */
#include <iostream>
#include <bitset>

using namespace std;

void print()
{
}

//notice:
//这里递归打印模板的可变参数，先是一个个的打印，打印到最后没有参数的时候
//会调用上面的没有参数的print函数。
//可以看成是一个参数和一包参数
template<typename T, typename... Types>
void print(const T& pFirstArg, const Types &... pTypes)
{
	//sizeof...(pTypes)可以知道除了第一个参数，后面还有多少个参数。
	cout << pFirstArg << "-------- " << sizeof...(pTypes) << endl; 
	print(pTypes...);
}

int main(int argc, char *argv[])
{
	print(1, 2.0, bitset<16>(16), "hello world!!!");	
	//print result
	//1-------- 3
	//2-------- 2
	//0000000000010000-------- 1
	//hello world!!!-------- 0

	return 0;
}
