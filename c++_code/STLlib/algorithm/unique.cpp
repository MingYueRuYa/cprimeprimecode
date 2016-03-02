/*
 * unique: 只能去掉连续重复的，如果不是的，则不能去掉
 * unique(b1, e1)
 * unique(b1, e1, op)
 * unique_copy(b1, e1, b2)
 * unique_copy(b1, e1, b2, op)
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <functional>
#include <set>

using namespace std;
using namespace std::placeholders;

bool AddOne(const int &pElement1, const int &pElement2)
{
	return pElement1 + 1 == pElement2;
}


int main(void)
{
	list<int> intlist{1, 1, 2, 2, 2, 3, 2, 4, 4, 1, 5, 6};
	list<int>::iterator ifind = unique(intlist.begin(), intlist.end());
	//for_each(intlist.begin(), ifind, [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	ifind = unique(intlist.begin(), intlist.end(), greater<int>());
	for_each(intlist.begin(), ifind, [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	

	list<int> intlist01{1, 1, 2, 2, 2, 3, 2, 4, 4, 1, 5, 6};
	//unique_copy(intlist01.begin(), intlist01.end(), ostream_iterator<int>(cout, " "));
	unique_copy(intlist01.begin(), intlist01.end(), ostream_iterator<int>(cout, " "));

	return 0;
}
