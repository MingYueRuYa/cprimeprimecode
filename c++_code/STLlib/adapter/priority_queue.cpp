/*
 * priority_queue 优先队列 适配器
 * 最大优先级队列，最小优先级队列
 * 默认是使用vector实现优先队列
 * 不能使用list实现优先队列，是因为在内部需要对数据进行随机访问， list不能随机访问
 * */

#include <iostream>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

int main(void)
{
	//默认使用最大优先级
	priority_queue<int> myqueue;
	//指定最小优先级
	priority_queue<int, deque<int>, greater<int>> mygreaterqueue;
	myqueue.push(-1);
	myqueue.push(1);
	myqueue.push(20);
	//cout << myqueue.top() << endl;
	cout << "element count " << myqueue.size() << endl;
	cout << endl;
	while (! myqueue.empty()) {
		cout << myqueue.top() << " ";
		myqueue.pop();
	}
	cout << endl;
	return 0;
}
