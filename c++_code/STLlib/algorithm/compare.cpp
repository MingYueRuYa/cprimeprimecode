/*
 * 关于比较的算法
 * equal 比较指定的范围时候相等
 * mismatch 找出第一个不匹配的
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>


using namespace std;

bool CompareValue(const int &pValue1, const int &pValue2)
{
	return pValue1 % 2 == pValue2 % 2;
}


int main_equal(void)
{
	vector<int> intvector;
	for (int i = 0; i < 10; ++i) {
		intvector.push_back(i);	
	}

	vector<int> intvector02;
	for (int i = 0; i < 5; ++i) {
		intvector02.push_back(i);	
	}

	//如果第一个范围比第二个范围大，就不相等,可以指定范围比较
	bool equalbool = equal(intvector.begin(), intvector.begin() + 5, intvector02.begin());
	if (equalbool) {
		cout << "equal." << endl;
	}
	
	//可以指定比较的方法
	equalbool = equal(intvector.begin(), intvector.begin() + 5, intvector02.begin(), CompareValue);
	if (equalbool) {
		cout << "equal." << endl;
	}

	return 0;
}

int main_mismatch(void)
{

	vector<int> intvector;
	for (int i = 1; i < 6; ++i) {
		intvector.push_back(i);
	}
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	list<int> intlist;
	for (int i = 1; i < 16; i *= 2) {
		intlist.push_back(i);
	}
	intlist.push_back(0);
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
		
	pair<vector<int>::iterator, list<int>::iterator> findpair = mismatch(intvector.begin(), intvector.end(), intlist.begin());
	if (findpair.first != intvector.end()) {
		cout << *findpair.first << " " << *findpair.second << endl;
	}

	//less_equal 预定义的谓词， 含义：找出第一个小于等于
	findpair = mismatch(intvector.begin(), intvector.end(), intlist.begin(), less_equal<int>());
	if (findpair.first != intvector.end()) {
		cout << *findpair.first << " " << *findpair.second << endl;
	}
	return 0;
}

void PrintCollecation(const list<int> &pList)
{
	for (list<int>::const_iterator begin = pList.begin(); begin != pList.end(); ++begin) {
		cout << *begin << " ";
	}
	cout << endl;
}

bool SortList(const list<int> &list01, const list<int> &list02)
{
	return lexicographical_compare(list01.begin(), list01.end(), list02.begin(), list02.end());
}

int main(void)
{
	list<int> list01, list02, list03, list04;
	for (int i = 0; i < 5; ++i) {
		list01.push_back(i);
	}
	list04 = list03 = list02 = list01;

	list02.push_back(0);
	list03.push_back(2);
	list03.push_back(4);
	list04.push_back(7);

	vector<list<int>> listvector;
	listvector.push_back(list01);
	listvector.push_back(list03);
	listvector.push_back(list02);
	listvector.push_back(list04);
	listvector.push_back(list01);
	listvector.push_back(list03);
	listvector.push_back(list02);
	listvector.push_back(list04);

	for_each(listvector.begin(), listvector.end(), PrintCollecation);
	cout << endl;

	sort(listvector.begin(), listvector.end(), SortList);

	for_each(listvector.begin(), listvector.end(), PrintCollecation);

	return 0;
}


