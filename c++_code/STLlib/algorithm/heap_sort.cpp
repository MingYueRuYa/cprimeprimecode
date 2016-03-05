/*
 * 堆排序->分为大堆和小堆排序，本质都是二叉树
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <iterator>
#include <functional>

using namespace std;

int main(void)
{
	vector<int> ivec{9, 8, 5, 6, 7, 2, 3, 1};
	make_heap(ivec.begin(), ivec.end());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	//pop_heap 把当前最大的放到vector的最后面
	pop_heap(ivec.begin(), ivec.end());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	//删除最后面的最大值
	ivec.pop_back();
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	
	ivec.push_back(12);
	push_heap(ivec.begin(), ivec.end());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	sort_heap(ivec.begin(), ivec.end());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	return 0;
}
