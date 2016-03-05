/*
 * sort(b1, e1)
 * sort(b1, e1, op)
 * stable_sort(b1, e1)
 * stable_sort(b1, e1, op)
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <iterator>
#include <functional>

using namespace std;

bool CompareLength(const string &pElement1, const string &pElement2)
{
	return pElement1.length() > pElement2.length();
}

int main(void)
{
	deque<int> ideq{1, 5, 2, 3, 6, 7, 4, 9, 8};
	sort(ideq.begin(), ideq.end());
	for_each(ideq.begin(), ideq.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	
	sort(ideq.begin(), ideq.end(), greater<int>());
	for_each(ideq.begin(), ideq.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	vector<string> strvector;
	strvector.push_back("10");
	strvector.push_back("xx");
	strvector.push_back("17xx");
	strvector.push_back("17xxx");
	strvector.push_back("12");
	strvector.push_back("13");
	strvector.push_back("14");
	strvector.push_back("14");
	strvector.push_back("xxx");
	stable_sort(strvector.begin(), strvector.end());
	for_each(strvector.begin(), strvector.end(), [](const string &pValue){ cout << pValue << " ";});
	cout << endl;

	stable_sort(strvector.begin(), strvector.end(), CompareLength);
	for_each(strvector.begin(), strvector.end(), [](const string &pValue){ cout << pValue << " ";});
	cout << endl;

	return 0;
}


