/*
 * remove(b1, e1, value)
 * remove_if(b1, e1, op, value)
 * attention:
 * 		1.并不是真正的删除算法，而是把后面的元素向前移动，覆盖被删除的元素
 * 		2.返回性的逻辑终点
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <functional>

using namespace std;
using namespace std::placeholders;

int main(void)
{
	list<int> intlist{1, 1, 2, 3, 3, 4, 1, 2, 5, 6};
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	//返回的是逻辑重点，算法不会对容器进行操作,所以不会删除容器中元素
	list<int>::iterator end = remove(intlist.begin(), intlist.end(), 1);
	for (list<int>::iterator begin = intlist.begin(); begin != end; ++begin) {
		cout << *begin << " ";
	}
	intlist.erase(end, intlist.end());
	cout << endl;

	//同样是的，返回的是逻辑重点，算法不会对容器进行操作,所以不会删除容器中元素
	intlist.erase(remove_if(intlist.begin(), intlist.end(), bind(less<int>(), _1, 4)), intlist.end());
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});


	return 0;
}
