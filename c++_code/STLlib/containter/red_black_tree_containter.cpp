/*
 * 红黑树容器
 * */
#include <iostream>
#include <set>

using namespace std;

int main()
{
	set<int> myset;
	myset.insert(10);
	myset.insert(9);
	myset.insert(8);
	myset.insert(7);
	//插入重复的会被舍弃
	myset.insert(7);
	myset.insert(6);
	auto findpos = myset.find(10);
	cout << *findpos << "\n";
	auto ibegin = myset.rbegin();
	auto iend = myset.rend();
	for (; ibegin != iend; ibegin++) {
		cout << *ibegin << "\n";
	}
	return 0;
}
