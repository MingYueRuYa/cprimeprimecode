/*
 * replace(b1, e1, oldvalue, newvalue)
 * replace_if(b1, e1, op, newvalue)
 * replace_copy(b1, e1, b2, oldvalue, newvalue)
 * replace_copy_if(b1, e1, b2, op, newvalue)
 * */

#include <iostream>
#include <algorithm>
#include <list>
#include <functional>
#include <string>

using namespace std;
using namespace std::placeholders;

void TestBind(int x, int y, string name)
{
	cout << x + y << endl;
	cout << name << endl;
}

int main(void)
{
	list<int> intlist{1, 2, 3, 4, 5, 6, 7};	
	replace(intlist.begin(), intlist.end(), 1, 2);
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	//less 5 replace to 2.
	replace_if(intlist.begin(), intlist.end(), bind(less<int>(), _1, 5), 2);
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;


	list<int> intlist02{2, 4, 6, 8, 10, 12, 14};
	replace_copy(intlist.begin(), intlist.end(), intlist02.begin(), 5, 6);
	for_each(intlist02.begin(), intlist02.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;	

	replace_copy_if(intlist.begin(), intlist.end(), intlist02.begin(), bind(equal_to<int>(), _1, 2), 5);
	for_each(intlist02.begin(), intlist02.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;	

	/***************************************************/
//	auto callable = bind(TestBind, _1, 1, "linux");	
//	callable(2);
	/***************************************************/

	return 0;
}


