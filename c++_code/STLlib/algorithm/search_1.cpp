/*
 * search 从前面开始找
 * find_end 从后面开始找
 * 	在一个容器中查找一个子区间
 * */

#include <iostream>
#include <deque>
#include <list>
#include <algorithm>

using namespace std;

bool CheckEven(int pElement, bool pIsEven)
{
	if (pIsEven) {
		return pElement % 2 == 0;
	} else {
		return pElement % 2 == 1;
	}

}

int main(void)
{
	deque<int> intdeque;
	for (int i = 0; i < 7; ++i) {
		intdeque.insert(intdeque.end(), i);
	}
	bool CheckBool[3] = {true, false, true};
	//从intdeque中找出 偶数和奇数和偶数 
	//注意CheckBool的范围取值, +3 表示和迭代器类似原理
	deque<int>::iterator ifind = search(intdeque.begin(), intdeque.end(), CheckBool, CheckBool + 3, CheckEven);
	if (ifind != intdeque.end()) {
		cout << distance(intdeque.begin(), ifind) + 1 << endl;
	}
	return 0;
}

int main01(void)
{
	deque<int> intdeque;
	for (int i = 0; i < 7; ++i) {
		intdeque.insert(intdeque.end(), i);
	}

	for (int i = 0; i < 7; ++i) {
		intdeque.insert(intdeque.end(), i);
	}

	list<int> intlist;
	for (int i = 3; i < 6; ++i) {
		intlist.insert(intlist.end(), i);
	}
	/*
	deque<int>::iterator ifind = search(intdeque.begin(), intdeque.end(), intlist.begin(), intlist.end());
	if (ifind != intdeque.end()) {
		cout << "find number sequence index is " << distance(intdeque.begin(), ifind) << endl;
	}
	++ifind;
	ifind = search(ifind, intdeque.end(), intlist.begin(), intlist.end());
	if (ifind != intdeque.end()) {
		cout << "find number sequence index is " << distance(intdeque.begin(), ifind) << endl;
	}
	*/
	deque<int>::iterator ifind = intdeque.begin();
	while (ifind != intdeque.end()) {
		ifind++;
		ifind = search(ifind, intdeque.end(), intlist.begin(), intlist.end());
		if (ifind != intdeque.end()) {
			cout << "find number sequence index is " << distance(intdeque.begin(), ifind) << endl;
		}
	}
	//从后面往前面开始找
	ifind = find_end(intdeque.begin(), intdeque.end(), intlist.begin(), intlist.end());
	if (ifind != intdeque.end()) {
		cout << "find number sequence index is " << distance(intdeque.begin(), ifind) << endl;
	}
	return 0;
}


