/*
 * 常见的宏和静态断言
 * __FUNCTION__ 不能使用
 **/

#include <iostream>
#include <assert.h>
#include <stdio.h>

using namespace std;


//common macro
int main01()
{
	int num = 100;
	cout << __FILE__ << endl;
	cout << __LINE__ << endl;
	cout << __DATE__ << endl;
	cout << __TIME__ << endl;
	//cout << __FUNCTION___ << endl;
	return 0;
}

#define M
int main()
{
	char num = 10;
	cout << sizeof(num) << endl;
#ifdef M
	//满足这个条件，静态断言为真，则编译通过。否则为假，编译不能通过
	static_assert(sizeof(num) <= 4, "linux error");
#endif
	return 0;
}
