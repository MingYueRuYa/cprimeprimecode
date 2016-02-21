/*
 * queue 适配器
 * queue<int, list<int>> 
 * queue<int, deque<int>>
 * size empty front back push pop 
 * 不能使用vector 实现queue，因为queue需要在两头进行操作
 * */

#include <iostream>
#include <queue>

//双端队列
#include <deque>
//提供了二维动态数组的功能，头部，尾部，任意操作

using namespace std;

int main(void)
{
	queue<int, deque<int>> myqueue;
	myqueue.push(1);
	myqueue.push(2);
	myqueue.push(3);
	myqueue.push(4);
	cout << "front "<< myqueue.front()  << " back: " << myqueue.back() << endl;
	return 0;
}

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
int main02()
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
