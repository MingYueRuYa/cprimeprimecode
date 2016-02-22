/*
 * 算法的概念
 * */
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

class myprint01
{
public:
	void operator() (int t)
	{
		cout << t << endl;
	}
};

template<class T>
class myprint
{
public:
	void operator() (const T &t)
	{
		cout << t << endl;
	}
};

struct print
{
	void operator()(int num)
	{
		cout << num << endl;
	}
	void Print(int num)
	{
		cout << num << endl;
	}
};

void printNum(int num)
{
	cout << num << endl;
}

int main02()
{
	vector<int> myvector;
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);
	myvector.push_back(4);
	myprint<int> printnum;
	myprint01 printnum01;
	//模板
	//for_each(myvector.begin(), myvector.end(), printNum);
	//非模板 class
	//for_each(myvector.begin(), myvector.end(), printnum01);
	struct print print02;
	for_each(myvector.begin(), myvector.end(), print02);
	return 0;
}

int main01()
{
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//首地址a开始，a+10表示最后一个地址，但是注意最后一个在数组中不存在的。
	//int *p = find(a, a + 10, 8);
	int *p = find(a, a + 10, 0);
	std::cout << (void *)a << " " <<(void *)(a + 10) << endl;
	std::cout << *p << std::endl;
	if (p == a + 10) {
		std::cout << "Not find.\n";	
	}
	//遍历数组中每一个元素
	//起始地址，终止地址，函数指针
	//for_each(a, a + 4, printNum);
	//重载了结构体中()运算符
	for_each(a, a + 4, print());
	return 0;
}

//find_if find_if_not
int main03()
{
	vector<int> myvector;
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);
	myvector.push_back(2);
	myvector.push_back(5);
	//查询第一个大于4
	//auto i = find_if(myvector.begin(), myvector.end(), [](int v)->bool{ return (v > 4); });
	//查找第一个小于4
	auto i = find_if_not(myvector.begin(), myvector.end(), [](int v)->bool{ return (v > 4); });
	if (i != myvector.end()) {
		cout << *i <<endl;
	} else {
		cout << "Not find.\n";
	}

	return 0;
}

template<class T>
class Show
{
public:
	void operator()(T &t)
	{
		cout << t << "  ";
	}
};

//find 
int main04()
{
	list<int> mylist;
	vector<int> myvector;
	mylist.push_back(11);
	mylist.push_back(22);
	mylist.push_back(3);
	mylist.push_back(4);
	mylist.push_back(4);

	myvector.push_back(21);
	myvector.push_back(2);
	myvector.push_back(33);
	myvector.push_back(4);
	myvector.push_back(4);
	//报错，算法依赖于数据结构（链式，线性），不同的数据结构，算法不一样
	//sort(mylist.begin(), mylist.end());
	sort(myvector.begin(), myvector.end());
	//for_each(mylist.begin(), mylist.end(), [](int v){ cout << v << endl;});
	for_each(myvector.begin(), myvector.end(), [](int v){ cout << v << endl;});
	cout << "\n";
	//填充，指定位置数据进行初始化
	fill(myvector.begin() + 3, myvector.end(), 3);
	for_each(myvector.begin(), myvector.end(), [](int v){ cout << v << endl;});
	cout << "\n";

	for_each(myvector.begin(), myvector.end(), Show<int>());
	return 0;
}

int main()
{
	multiset<int>myset;
	myset.insert(1);
	myset.insert(2);
	myset.insert(1);
	myset.insert(1);
	myset.insert(3);
	myset.insert(4);
	//统计 1 有多少个节点
	int num = count(myset.begin(), myset.end(), 1);
	cout << num << endl;
	return 0;
}
