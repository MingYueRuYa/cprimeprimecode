/*
 * count 和 find算法
 * count 用于计数返回个数
 * find 用于查找返回iterator
 * */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
bool IsEvent(T t)
{
	return (t % 2 == 0);
}

int main(void)
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
