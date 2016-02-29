/*
 * fill
 * fill_n
 * generate
 * generate_n
 * */

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <iterator>

using namespace std;

int main(void)
{
	list<string> stringlist(10, "hi");	
	for_each(stringlist.begin(), stringlist.end(), [](const string &pValue){ cout << pValue << " ";});
	cout << endl;

	fill(stringlist.begin(), stringlist.end(), "hello");
	for_each(stringlist.begin(), stringlist.end(), [](const string &pValue){ cout << pValue << " ";});
	cout << endl;

	//fill_n(stringlist.begin(), 5, "linux");
	list<string>::iterator begin = stringlist.begin();
	fill_n(++begin, 5, "linux");
	for_each(stringlist.begin(), stringlist.end(), [](const string &pValue){ cout << pValue << " ";});
	cout << endl;

	fill_n(ostream_iterator<string>(cout, " "), 5, "window");

	list<int> intlist(10, 2);
	generate_n(intlist.begin(), 5, rand);
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	generate(intlist.begin(), intlist.end(), rand);
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	return 0;
}

