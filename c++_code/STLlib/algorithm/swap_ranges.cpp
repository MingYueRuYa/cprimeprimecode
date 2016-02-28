/*
 * swap_ranges(b, e, b2)
 * 注意：下列两中方法也算是交换算法
 * 		1.容器的swap()成员函数
 * 		2.赋值操作
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int main(void)
{
	vector<int> ivec{1, 2, 3, 4, 5};	
	list<int> ilist{6, 7, 8, 9, 10, 11};
	
	//*************if ivec size is bigger than ilist 
	//*************then occur Segmentation fault
	swap_ranges(ivec.begin(), ivec.end(), ilist.begin());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	for_each(ilist.begin(), ilist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	//if vector have same type, we can use swap member function.
	vector<int> ivec02{11, 12, 13, 14, 15};
	//it's faster than swap_ranges, because inside it's change pointer to pointer other.
	ivec02.swap(ivec);
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	for_each(ivec02.begin(), ivec02.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	//assign, this is also swap, but this is function slow(because inside call copy constructer), and ivec not save before value.
	ivec = ivec02;
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	return 0;
}
