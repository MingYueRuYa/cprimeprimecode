/*
 * lambda表达式
 * */

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;
/**********************************************
*notice:
*[](){cout << "hello world!" << endl}; 这是一个函数指针
*[](){cout << "hello world!" << endl}(); 这是函数调用
**********************************************/

int main01()
{
	auto fun1 = [](){ cout <<"hello world!" << endl; };
	fun1();
	auto func2 = [](int a, int b){ cout << a + b << endl << endl; };
	func2(1, 2);
	return 0;
}

int main02()
{
	vector<int> myvector;
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(11);
	auto fun1 = [](int v){cout << v << endl;};
	for_each(myvector.begin(), myvector.end(), fun1);
	return 0;
}

int main03()
{
	vector<int> myvector;
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(11);
	int a = 10;
	//= 表示知道a的存在，可以引用，只能读，不可以写或者是修改，引用当前块语句内部的局部变量
	auto fun1 = [=](int v){ v += a; cout << v << endl;};
	for_each(myvector.begin(), myvector.end(), fun1);
	cout << a << endl;
	return 0;
}

int main05()
{
	vector<int> myvector;
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(11);
	int a = 10, b = 0;	
	//&引用块语句中的所有变量， &a表示引用块语句中a变量
	auto fun1 = [&a](int v) { a += 20, v += a; cout << v << endl;};
	//auto fun1 = [&](int v) { a += 20, b = 10, v += a; cout << v << endl;};
	for_each(myvector.begin(), myvector.end(), fun1);
	cout << "a:" << a << " b:" << b <<endl;
	return 0;
}

class test
{
public:
	vector<int> myvector;
	int num;
public:
	test()
	{
		num = 12;
		myvector.push_back(10);
		myvector.push_back(11);
	}

	void add() {
		//[]引用this
		int x = 3;
		auto fun1 = [this, x](int v) { cout << v + x + this->num << endl;};
		for_each(myvector.begin(), myvector.end(), fun1);
	}
};


int main()
{
	//lambda返回值
	auto fun1 = []()->double{ cout << "china" << endl; return 1;};
	cout << fun1() << endl;
	int a = 10;
	auto fun2 = [a](int v)mutable->double{ v += a; cout << v << endl; a = 3; return 3; };
	cout << fun2(1) << endl;
	cout << a << endl;
	return 0;
}

