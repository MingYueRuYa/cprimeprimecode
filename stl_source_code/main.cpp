/*
 * 学习2.9版本的stl source code.
 * */

#include <iostream>
#include "vector"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	vector<int> vec;
	for (int i=0; i<10; ++i) {
		vec.push_back(i);
	}

	for (int i=0; i<10; ++i) {
		cout << vec[i] << endl;
	}

	return 0;
}
