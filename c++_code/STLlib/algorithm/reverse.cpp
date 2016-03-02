/*
 * 反转
 * reverse
 * reverse_copy 
 * */

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

int main_reverse(void)
{
	vector<int> intvector{1, 2, 3, 4, 5, 6, 7};
	reverse(intvector.begin(), intvector.end());
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	//随机迭代器可以进行加法运算
//	reverse(intvector.begin() + 1, intvector.end() - 2);
//	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	
	vector<int> intvector02;
	reverse_copy(intvector.begin(), intvector.end(), back_inserter(intvector02));
	for_each(intvector02.begin(), intvector02.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	rotate(intvector.begin(), intvector.begin() + 2, intvector.end());	
	rotate(intvector.begin(), find(intvector.begin(), intvector.end(), 2), intvector.end());	
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	return 0;
}

int main(void)
{
	set<int> intset{1, 2, 3, 4, 5, 6, 7, 8};
	set<int>::iterator ipos = intset.begin();
	advance(ipos, 4);
	//rotate(intset.begin(), ipos, intset.end());
	//for_each(intset.begin(), intset.end(), [](const int &pValue){ cout << pValue << " ";});

	rotate_copy(intset.begin(), ipos, intset.end(), ostream_iterator<int>(cout, " "));
	return 0;
}

