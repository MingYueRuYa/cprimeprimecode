/*
 * stack
 * */
#include <stack>
#include <iostream>

using namespace std;

int main()
{
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	stack<int> mystack;
	for (int i = 0; i < 10; i++) {
		mystack.push(a[i]);
	}
	while (! mystack.empty()) {
		cout << mystack.top() << "\n";
		mystack.pop();
	}
	return 0;
}
