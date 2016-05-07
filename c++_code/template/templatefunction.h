/*
 * template function
 * */

#include <iostream>

using namespace std;

template<typename T> inline
int compare(const T &t1, const T &t2)
{
//	if (t1 < t2) {
//		return -1;
//	}
//	if (t2 < t1) {
//		return 1;
//	}
	//improve version
	//this version can compare pointer type.
	if (less<T>(t1, t2)) {
		return -1;
	}
	if (less<T>(t2, t1)) {
		return 1;
	}
	return 0;
}

void test();
