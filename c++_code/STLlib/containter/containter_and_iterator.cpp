/*
 * 容器和迭代器
 * */
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <list>

using namespace std;

bool less2(int x)
{
	return x < 2;
}

//list
int main()
{
	list<int>mylist;
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_back(4);
	auto ibegin = mylist.begin();
	auto iend = mylist.end();
	for (; ibegin != iend; ibegin++) {
		cout << *ibegin << "\n"; 
		printf("%p\n", ibegin);
		//智能指针，STL bug， 分行打印，先访问内部，在访问外部
		//printf("%p, %p\n", ibegin._Ptr, ibegin);
	}
	return 0;
}

//vector
int main01()
{
	vector<int>myvector;
	myvector.push_back(1);
	myvector.push_back(2);
	myvector.push_back(3);
	myvector.push_back(1);
	
	auto ibegin = myvector.begin();
	auto iend = myvector.end();
	for (; ibegin != iend; ibegin++) {
		cout << *ibegin << "\n";
	}
	//仿函数可以实现一定的算法策略
	
	//auto ifind = find_if(++myvector.begin(), myvector.end(), bind1st(greater<int>(), 4));
	//auto ifind = find_if(myvector.begin(), myvector.end(), bind1st(greater<int>(), 4));
	//bind1st(greater<int>(), 4)
	//绑定一个函数,greater<int>(), 4
	auto ifind = find_if(myvector.begin(), myvector.end(), less2);
	cout << *ifind << "\n";
	return 0;
}
