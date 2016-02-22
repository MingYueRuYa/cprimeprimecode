/*
 * count 和 find通用算法
 * count 用于计数返回个数
 * find 用于查找返回iterator
 * 关联容器等效成员函数
 * 	set.count multiset.count map.count multi.count 此成员函数效率比较高
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <set>

using namespace std;

template <typename T>
bool IsEvent(T t)
{
	return (t % 2 == 0);
}

int main(void)
{
	vector<int> intvector;
	for (int i = 0; i < 9; ++i) {
		intvector.push_back(i);	
	}

	//bind2nd 函数适配器 greate<int>(int num1, int num2) 需要两个参数，第二个绑定为4
	//greate<int>(int num1, int num2) 为预定于函数 存在于functional头文件中
	int num = count_if(intvector.begin(), intvector.end(), bind2nd(greater<int>(), 4));
	//not1是适配器，表示不是1， modulus表示求模运算
	int evennum = count_if(intvector.begin(), intvector.end(), not1(bind2nd(modulus<int>(), 2)));
	cout << "even nums " << evennum << endl;
	cout << num << endl;

	multiset<int> myset;
	for (int i = 0; i <= 10; ++i) {
		myset.insert(i);
	}
	myset.insert(10);
	num = count(myset.begin(), myset.end(), 10);
	cout << "一共有"  << num<< "个10" << endl;

	return 0;
}

int main01(void)
{
	
	vector<int> intvector{1, 2, 3, 4, 5, -1, -2, 2};
	size_t intcount = count(intvector.begin(), intvector.end(), 2);	
	cout << intcount << endl << endl;

	size_t eventcount = count_if(intvector.begin(), intvector.end(), IsEvent<int>);
	cout << eventcount << endl << endl;

	vector<int>::iterator ifind = find(intvector.begin(), intvector.end(), 3);
	if (ifind != intvector.end()) {
		cout << "find number " << *ifind << endl << endl;
	} else {
		cout << "not find." << endl;
	}

	ifind = find_if(intvector.begin(), intvector.end(), IsEvent<int>);
	if (ifind != intvector.end()) {
		cout << "find event " << *ifind << endl;
		cout << "index " << distance(intvector.begin(), ifind) << endl;
	} else {
		cout << "not find." << endl;
	}
	return 0;
}
