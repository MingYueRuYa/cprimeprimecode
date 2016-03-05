/*
 * partial_sort(b1, b2, e1)
 * partial_sort(b1, b2, e1, op)
 * partial_sort_copy(b1, b2, e1)
 * partial_sort_copy(b1, b2, e1, op)
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
#include <set>

using namespace std;

int main(void)
{
	vector<int> ivec{1, 3, 2, 6, 7, 5, 9, 8, 4};		
	//partial_sort(b1, b2, e1)
	partial_sort(ivec.begin(), ivec.begin() + 5, ivec.end());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	
	//partial_sort(b1, b2, e1)
	partial_sort(ivec.begin(), ivec.begin() + 5, ivec.end(), greater<int>());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	vector<int> ivec02(6);		
	//partial_sort_copy(b1, e1, b2, e2);
	partial_sort_copy(ivec.begin(), ivec.end(), ivec02.begin(), ivec02.end());
	for_each(ivec02.begin(), ivec02.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	
	//partial_sort_copy(b1, e1, b2, e2, op);
	partial_sort_copy(ivec.begin(), ivec.end(), ivec02.begin(), ivec02.end(), greater<int>());
	for_each(ivec02.begin(), ivec02.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	return 0;
}
