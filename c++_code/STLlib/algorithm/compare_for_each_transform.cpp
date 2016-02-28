/*
 * compare for_each transform algorithm 
 * for_each		high speed 		not flexable
 * transform	slow speed		flexable
 * */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//-------------------------------------------------------------
//
void Square01(int &pValue)
{
	pValue *= pValue;
	cout << pValue << " ";
}

int Square02(const int &pValue)
{
	return pValue * pValue;
}
//-------------------------------------------------------------

int main(void)
{
	vector<int> v1{1, 2, 3, 4, 5, 6};
	vector<int> v2{1, 2, 3, 4, 5, 6};
	for_each(v1.begin(), v1.end(), Square01);
	cout << endl;
	transform(v2.begin(), v2.end(), v2.begin(), Square02);
	for_each(v2.begin(), v2.end(),[](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	return 0;
}

