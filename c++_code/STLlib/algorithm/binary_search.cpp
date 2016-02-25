/*
 * 二分查找
 * */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main(void)
{
	list<int> intlist;
	for (int i = 0; i < 10; ++i) {
		intlist.insert(intlist.end(), i);
	}
	for_each(intlist.begin(), intlist.end(), [](int pElement){ cout << pElement << " "; });
	cout << endl;
	bool ifind = binary_search(intlist.begin(), intlist.end(), 5);
	if (ifind) {
		cout << "find value. " << endl;
	}
	return 0;
}
