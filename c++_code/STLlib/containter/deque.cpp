/*
 * deque 学习
 * 数据可以插入到前面和后面，vector只能插入到后面
 * */

#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

void Print(int pValue)
{
	cout << pValue << endl;
}

int main(void)
{
	deque<int> mydeques{1, 2, 3, 4};
	//for_each(mydeques.begin(), mydeques.end(), Print);
	mydeques.push_back(5);
	mydeques.push_front(0);
	for_each(mydeques.begin(), mydeques.end(), Print);
	cout << endl;
	mydeques.pop_front();
	mydeques.pop_back();
	for_each(mydeques.begin(), mydeques.end(), Print);
	cout << endl;

	deque<int>::iterator begin = mydeques.begin();
	for (; begin != mydeques.end(); ++begin) {
		size_t offset = distance(mydeques.begin(), begin);
		cout << "mydeque[" << offset << "] = " << *begin << endl;
	}	

	return 0;
}

