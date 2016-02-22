/*
 * serach 算法
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int main(void)
{
	vector<int> intvector;
	for (int i = -9; i < 10; ++i) {
		intvector.push_back(i);
	}
	intvector.push_back(9);	
	intvector.push_back(9);	
	
	list<int> intlist;
	for (int i = -8; i < 5; ++i) {
		intlist.push_back(i);
	}
	intlist.push_back(22);	

	vector<int>::iterator ifind = search(intvector.begin(), intvector.end(), intlist.begin(), intlist.end());
	if (ifind != intvector.end()) {
		cout << "postion " << distance(intvector.begin(), ifind) << endl;
	 } else {
		 cout << "not find " << endl;
	 }
	
	ifind = search_n(intvector.begin(), intvector.end(), 3, 9);
	if (ifind != intvector.end()) {
		cout << "postion " << distance(intvector.begin(), ifind) << endl;
	 } else {
		 cout << "not find " << endl;
	 }
	
	return 0;
}
