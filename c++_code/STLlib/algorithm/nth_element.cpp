/*
 * 根据第n个元素排序,比这个元素大的放在这个元素的左边或者右边
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>

using namespace std;

int main(void)
{
	vector<int> ivec{2, 3, 5, 5, 6, 3, 8, 9, 10};
	nth_element(ivec.begin(), ivec.begin() + 3, ivec.end());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	for_each(ivec.begin(), ivec.begin() + 4, [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	nth_element(ivec.begin(), ivec.begin() + 3, ivec.end(), greater<int>());
	for_each(ivec.begin(), ivec.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	
	return 0;
}
