#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int main(void)
{
	vector<int>	 intvector;
	intvector.push_back(1);
	intvector.push_back(2);
	intvector.push_back(3);
	
	auto begin = intvector.begin();
	/*
	while (begin != intvector.end()) {
		cout << *begin << endl;
		++begin;
	}
	*/
	intvector.push_back(4);
	//插入 使begin 迭代器失效
	intvector.insert(begin + 2, 100);
	begin = intvector.begin();
	while (begin != intvector.end()) {
		cout << *begin << endl;
		++begin;
	}
	//cout << *begin << endl;
	return 0;
}
