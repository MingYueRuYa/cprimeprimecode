/*
 * partition 不稳定分区
 * stable_partition 稳定分区
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
using namespace std::placeholders;

bool Even(const int &pValue)
{
	return pValue % 2 == 1;
}


int main(void)
{
	vector<int> intvector{1, 2, 3, 4, 5, 6, 7, 8, 9};	
	//thi is way, complier will error.
	//partition(intvector.begin(), intvector.end(), not1(bind(modulus<int>(), _1, 2)));
	partition(intvector.begin(), intvector.end(), Even);
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl << "stable_partition: " << endl;
	vector<int> intvector01 = intvector;
	//stable_partition(intvector01.begin(), intvector01.end(), Even);
	stable_partition(intvector01.begin(), intvector01.end(), not1(bind2nd(modulus<int>(), 2)));
	for_each(intvector01.begin(), intvector01.end(), [](const int &pValue){ cout << pValue << " ";});

	//thi is way, complier will not error.
	not1(bind2nd(modulus<int>(), 2));

	return 0;
}

