/*
 * random sort
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <functional>

using namespace std;

int main(void)
{
	list<int> intlist{1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<int> intvector{1, 2, 3, 4, 5, 6, 7, 8, 9};
	random_shuffle(intvector.begin(), intvector.end());
	//不适合链式容器
	//random_shuffle(intlist.begin(), intlist.end());
	//for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	return 0;
}

