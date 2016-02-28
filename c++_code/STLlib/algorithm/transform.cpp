/*
 * transform tow style
 * transform(b1, e1, b2, op)
 * transform(b1, e1, b2, b2, op)
 * 注意：
 * 	1.如果目标与源相同，transform()和for_each()一样。
 * 	2.如果想以某值替换符合规则的元素，应使用replace()算法
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <functional>

using namespace std;

int main01(void)
{
	vector<int> intvector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//预定义的谓词
	transform(intvector.begin(), intvector.end(), intvector.begin(), negate<int>());	
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	
	transform(intvector.begin(), intvector.end(), intvector.begin(), bind2nd(multiplies<int>(), 10));	
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	list<int> intlist;
	transform(intvector.begin(), intvector.end(), back_inserter(intlist), bind2nd(plus<int>(), 10));
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;	

	intlist.clear();
	transform(intvector.begin(), intvector.end(), ostream_iterator<int>(cout, " "), negate<int>());
	//for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	return 0;
}

//利用transform合并
int main(void)
{
	vector<int> intvector{1, 2, 3, 4, 5, 6, 7, 8, 9};
	list<int> intlist(9, 0);//{1, 2, 3, 4, 6, 7, 8, 9};
	transform(intvector.begin(), intvector.end(), intvector.rbegin(), intlist.begin(), minus<int>());
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;	

	transform(intvector.begin(), intvector.end(), intvector.rbegin(), intvector.begin(), multiplies<int>());
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;	

	return 0;
}

