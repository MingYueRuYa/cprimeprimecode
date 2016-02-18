/*
 * vector 练习
 * */

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

void print(const int &pNum)
{
	cout << pNum << endl;		
}

int main(int argc, char *argv[])
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
