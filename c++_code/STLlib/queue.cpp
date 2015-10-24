/*
 * 队列
 * */

#include <iostream>
#include <queue>

//双端队列
#include <deque>
//提供了二维动态数组的功能，头部，尾部，任意操作

using namespace std;

int main01()
{
	queue<char *>myqueue;
	myqueue.push("ifconfig");
	//myqueue.push("firefox &");
	myqueue.push("pwd");
	while (! myqueue.empty()) {
		char *pstr = myqueue.front();
		system(pstr);
		myqueue.pop();
	}

	return 0;
}

//双端队列
int main()
{
	deque<int> mydeque;
	mydeque.push_back(1);
	mydeque.push_back(11);
	mydeque.push_back(111);
	mydeque.push_back(1111);

	mydeque.push_front(123);
	mydeque.insert(mydeque.begin() + 3, 2222);
	//head pop
	mydeque.pop_front();
	//tail pop
	mydeque.pop_back();
	for (int i = 0; i < mydeque.size(); i++) {
		cout << mydeque[i] << "\n";
	}
	//利用迭代器访问
	auto ibegin = mydeque.begin();
	auto iend = mydeque.end();
	for (;ibegin != iend; ibegin++) {
		cout << *ibegin << endl;
	}
	return 0;
}





