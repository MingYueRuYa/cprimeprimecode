/*
 * vector 练习
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

void print(const int &pNum)
{
	cout << pNum << endl;		
}

void printstr(const string &pNum)
{
	cout << pNum << endl;		
}

int main01(int argc, char *argv[])
{
	vector<int> intvector = {1, 2, 3};
	for_each(intvector.begin(), intvector.end(), print);
	vector<int> intvector01(10, -1);
	//for_each(intvector01.begin(), intvector01.end(), print);
	//vector<int> intvector02(intvector01.begin(), intvector01.end());
	//for_each(intvector02.begin(), intvector02.end(), print);
	vector<int> intvector03 = intvector;
	//for_each(intvector03.begin(), intvector03.end(), print);
	vector<int>::iterator begin = intvector.begin();
	vector<int>::iterator insertiterator = intvector.insert(begin, 4);
	cout << *insertiterator;
	return 0;
}

int main(int argc, char *argv[])
{
	vector<string> vectorstring;
	string inputstr;
	while (cin >> inputstr) {
		vectorstring.push_back(inputstr);
	}
	for_each(vectorstring.begin(), vectorstring.end(), printstr);
	return 0;
}

