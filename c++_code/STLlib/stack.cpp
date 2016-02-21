/*
 * stack 适配器
 * empty size pop push top
 * */
#include <iostream>
#include <stack>
#include <deque>
#include <vector>
#include <list>

using namespace std;

int main()
{
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	stack<int> mystack;
	for (int i = 0; i < 10; i++) {
		mystack.push(a[i]);
	}
	cout << "stack size: " << mystack.size() << "\n";
	while (! mystack.empty()) {
		cout << mystack.top() << "\n";
		mystack.pop();
	}
	//第一个参数指定类型，第二个参数指定stack实现的方式，默认实现方式为deque
	stack<int, deque<int>> coustomstatck01;
	stack<int, vector<int>> coustomstatck02;
	stack<int, list<int>> coustomstatck03;

	return 0;
}
