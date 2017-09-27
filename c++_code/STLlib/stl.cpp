/****************************************************************************
***
*** Copyright (C) 2017 liushixiongcpp@163.com (http://www.2144.cn)
*** All rights reserved.
***
*****************************************************************************/
/*
 * study stl from houjie master
 * 2017年 09月 26日 星期二 14:55:47 CST
 *
 * */

#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>

const long ASIZE = 500000L;

using std::cin;
using std::cout;
using std::endl;
using std::string;

long get_a_target_long()
{
	long target = 0;
	cout << "target (0~" << RAND_MAX << "): ";
	cin >> target;
	return target;
}

string get_a_target_string()
{
	long target = 0;
	char buff[10];
	cout << "target (0~" << RAND_MAX << "): ";
	cin >> target;
	snprintf(buff, 10, "%ld", target);
	return string(buff);
}

int compareLongs(const void *a, const void *b)
{
	return (*(long *)a - *(long *)b);
}

int compareString(const void *a, const void *b)
{
	if (*(string *)a > *(string *)b) { return 1; }
	else if (*(string *)a < *(string *)b) { return -1; }
	else { return 0; }
}


//-------------------------------------------------
#include <ctime>
#include <array>
#include <cstdlib> //qsort, bsarch 
//#include <iostream>

using std::array;

namespace test_array
{
	void test_array()
	{
		std::cout << "............test array............" << std::endl;
		srand(time(NULL));
		array<long, ASIZE> c;
		clock_t timestart = clock();
		for (long i=0; i<ASIZE; ++i) {
			c[i] = rand();
		}

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "array.size()= " << c.size() << endl;
		cout << "array.front()= " << c.front() << endl;
		cout << "array.back()= " << c.back() << endl;
		cout << "array.data()= " << c.data() << endl;

		long target = get_a_target_long();
		timestart = clock();
		::qsort(c.data(), ASIZE, sizeof(long), compareLongs);
		long *item = (long *)::bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);
		cout << "qsort()+bsearch(), seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		if (nullptr != item) { cout << "found, " <<*item << endl; }
		else { cout << "not found! " << endl; }

		cout << endl;
	}
};

#include <vector>
#include <stdexcept>

using std::vector;
using std::string;
using std::exception;

namespace test_vector
{
	void test_vector()
	{
		srand(time(nullptr));

		vector<string> c;
		char buf[10];
		clock_t timestart = clock();

		for (int i=0; i<1000000; ++i) {
			try {
				snprintf(buf, 10, "%d", rand());
				c.push_back(string(buf));
			}
			catch(exception &p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		}
		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "vector.size()= " << c.size() << endl;
		cout << "vector.max_size()= " << c.max_size() << endl;
		cout << "vector.front()= " << c.front() << endl;
		cout << "vector.back()= " << c.back() << endl;
		cout << "vector.data()= " << c.data() << endl;
		//result:
//			seconds: 0.259996
//			vector.size()= 1000000
//			vector.max_size()= 1073741823 //实际大小
//			vector.front()= 187158322
//			vector.back()= 128384975
//			vector.data()= 0xb6c95008
		//! 当size为1,000,000时插入时间为2.9s
		//! 当size为10,000,000时直接killed

	}

};

int main(int argc, char *argv[])
{
	//test_array::test_array();
	test_vector::test_vector();
	return 0;
}







