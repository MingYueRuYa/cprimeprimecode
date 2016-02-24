/*
 * find_first_of
 * 只要找到第一個
 * */
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

int main(void)
{
	vector<int> intvector;
	for (int i = 0; i < 10; ++i) {
		intvector.push_back(i);
	}
	vector<int>::iterator ibegin = intvector.begin();
	for (; ibegin != intvector.end(); ++ibegin) {
		cout << *ibegin << " ";
	}
	cout << endl;

	list<int> intlist;
	intlist.push_back(3);
	intlist.push_back(4);
	intlist.push_back(5);
	intlist.push_back(6);
	
	//只要找到list中任意第一個匹配項就可以了
	ibegin = find_first_of(intvector.begin(), intvector.end(), intlist.begin(), intlist.end());
	if (ibegin != intvector.end()) {
		cout << "index " << distance(intvector.begin(), ibegin) + 1 << endl;
	} else {
		cout << "Not find." << endl;
	}
	
	//如要要找最後一個匹配項的話，需要逆向迭代器
	vector<int>::reverse_iterator ifind = intvector.rbegin();
	ifind = find_first_of(intvector.rbegin(), intvector.rend(), intlist.begin(), intlist.end());
	//逆向迭代器轉變爲正向迭代器調用base(), 且不用在+1
	cout << "index " << distance(intvector.begin(), ifind.base()) << endl;
	
	//与string比较
	string num("0123456789");
	string str("xlke1xh2");
	string::size_type position = str.find_first_of(num);
	cout << position << endl;
	position = str.find_last_of(num);
	cout << position << endl;
	return 0;
}

