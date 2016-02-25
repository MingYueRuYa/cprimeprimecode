/*
 * include 时候包含所有 必须是有序的集合
 * */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main(void)
{
	list<int> intlist;
	for (int i = 0; i < 10; ++i) {
		intlist.insert(intlist.end(), i);
	}

	vector<int> intvector;
	intvector.push_back(3);
	intvector.push_back(4);
	intvector.push_back(2);
	
	bool isexsit = includes(intlist.begin(), intlist.end(), intvector.begin(), intvector.end());
	if (isexsit) {
		cout << "true." << endl;
	} else {
		cout << "false." << endl;
	}
}
