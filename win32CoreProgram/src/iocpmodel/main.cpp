/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

// #include "IOCPModel.h"
#include "iocpserver.h"

#include <iostream>

using std::cout;
using std::endl;


#include <vector>

using namespace std;

template<typename Iterator, typename Comparator>
void insertionSort(const Iterator & begin, const Iterator &end, Comparator lessthan)
{
	if (begin == end) {
		return;
	}
	Iterator j;

	for (Iterator p = begin+1; p!= end; ++p) {
		auto tmp = std::move(*p);
		for (j = p; j != begin&& lessthan(tmp, *(j - 1)); --j) {
			*j = std::move(*(j - 1));
			*(j-1) = std::move(tmp);
		}

	}

}

int main() {
	std::vector<int> c(6, 0);
	std::vector<int> a = { 34, 8, 64, 51, 32, 21 };

	insertionSort(a.begin(), a.end(), less<decltype(*(a.begin()))>{});
	for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
		std::cout << std::endl;
		std::cout << ' ' << *it;
		std::cout << '\n';
	}

	//	
	return 0;

}


int main01(int argc, char **argv)
{
	IOCPServer server;
	server.LoadSocketLib();
	server.Start();

//	CIOCPModel model;
//	model.LoadSocketLib();
//	model.Start();

	while (1) {
		Sleep(1000);
	}

	return 0;
}