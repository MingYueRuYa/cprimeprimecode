/*
 * permutation 排列组合 在排列之前一定是要按照顺序
 * next_permutation
 * prev_permutaion
 * */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	vector<int> intvector{1, 2, 3};
	//begin small to big
	while (next_permutation(intvector.begin(), intvector.end())) {
		for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
		cout << endl;
	}
	cout << endl;

	vector<int> intvector02{3, 2, 1};
	//begin big to small
	while (prev_permutation(intvector02.begin(), intvector02.end())) {
		for_each(intvector02.begin(), intvector02.end(), [](const int &pValue){ cout << pValue << " ";});
		cout << endl;
	}

	cout << endl;
	return 0;
}

