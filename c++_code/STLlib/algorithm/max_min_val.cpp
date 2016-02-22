/*
 * 最大值和最小值算法
 *
 * */

#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

bool AbsValue(int pValue1, int pValue2)
{
	int tmp1 = abs(pValue1);
	int tmp2 = abs(pValue2);
	return tmp1 < tmp2;
}

struct AbsValueClass
{
	bool operator() (int pValue1, int pValue2) 
	{
		int tmp1 = abs(pValue1);
		int tmp2 = abs(pValue2);
		return tmp1 < tmp2;
	}
};

int main(void)
{
	deque<int> mydeque;
	for (int i = -10; i < 10; ++i) {
		mydeque.insert(mydeque.end(), i);
	}
	deque<int>::iterator ibegin = mydeque.begin();
	while (ibegin != mydeque.end()) {
		cout << *ibegin << " ";
		++ibegin;
	}
	cout << endl;
	
	deque<int>::iterator imin = min_element(mydeque.begin(), mydeque.end());
	if (imin != mydeque.end()) {
		cout << "mini value is " << *imin << endl;
	}

	imin = max_element(mydeque.begin(), mydeque.end(), AbsValue);
	if (imin != mydeque.end()) {
		cout << "max value is " << *imin << endl;
	}

	imin = min_element(mydeque.begin(), mydeque.end(), AbsValueClass());
	if (imin != mydeque.end()) {
		cout << "mini value is " << *imin << endl;
	}

	return 0;
}
