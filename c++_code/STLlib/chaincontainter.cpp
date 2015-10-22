/*
 * 链式容器
 * */
#include <iostream>
#include <hash_set>
#include <list>
#include <stdio.h>

//list适用于经常插入，经常删除
//链式存储，不允许小标访问
using namespace std;

int main01()
{
	list<int> mylist;
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_back(4);
	//指针，指向一个迭代器，迭代器存储了位置
	auto ibegin = mylist.begin();
	auto iend = mylist.end();
	for (;ibegin != iend; ibegin++) {
		cout << *ibegin << "\n";
		//printf("%p, %p\n", ibegin._Ptr, ibegin);
	}

}

int main02()
{
	list<int> mylist;
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_back(4);
	//指针，指向一个迭代器，迭代器存储了位置
	auto ibegin = mylist.begin();
	auto iend = mylist.end();
	iend--;
	//end最后一个没有实体
	mylist.erase(iend);
	//重新计算iend位置
	iend = mylist.end();
	for (;ibegin != iend; ibegin++) {
		cout << *ibegin << "\n";
		//printf("%p, %p\n", ibegin._Ptr, ibegin);
	}
	//mylist.clear();清空所有
	//mylist.remove(4);根据元素删除
}

//插入
int main03()
{
	int a[5] = {1, 2, 3, 4, 5};
	list<int> mylist(a, a + 5);
	//尾部插入
	mylist.push_back(12);
	//头部插入
	mylist.push_front(0);
	auto ibegin = mylist.begin();
	auto iend = mylist.end();
	for (; ibegin != iend; ibegin++) {
		cout << *ibegin << "\n";
	}
	return 0;
}

//反序查找
int main04()
{
	int a[5] = {1, 2, 3, 4, 5};
	list<int> mylist(a, a + 5);
	auto ibegin = mylist.rbegin();
	auto iend = mylist.rend();
	for (; ibegin != iend; ibegin++) {
		cout << *ibegin << "\n";
	}
	return 0;
}


//排序和合并
int main05()
{
	int a[5] = {1, 2, 3,34, 5};
	list<int> mylist01(a, a + 5);
	int b[5] = {1, 23, 3, 4,15};
	list<int> mylist02(b, b + 5);
	mylist01.sort();	
	mylist02.sort();	
	//在合并之前一定要排序，否则会down
	mylist01.merge(mylist02);
	auto ibegin = mylist01.rbegin();
	auto iend = mylist01.rend();
	for (; ibegin != iend; ibegin++) {
		cout << *ibegin << "\n";
	}
	return 0;
}

//去除重复
int main()
{
	
	int a[7] = {1, 2, 3,34, 5, 5, 2};
	list<int> mylist01(a, a + 7);
	mylist01.sort();
	mylist01.unique();
	auto ibegin = mylist01.rbegin();
	auto iend = mylist01.rend();
	for (; ibegin != iend; ibegin++) {
		cout << *ibegin << "\n";
	}
	return 0;
}







