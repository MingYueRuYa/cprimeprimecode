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

#define SECONDS(mseconds) ((mseconds)*1.0/CLOCKS_PER_SEC)

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
#include <algorithm>

using std::vector;
using std::string;
using std::exception;

namespace test_vector
{
	void test_vector()
	{
		std::cout << "............test vector............" << std::endl;
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

		string target = get_a_target_string();
		{
			timestart = clock();
			auto item = find(c.begin(), c.end(), target);
			cout << "std::find(), seconds:" << SECONDS(clock()-timestart) << endl;
			if (c.end() != item) { cout << "found, " << *item << endl; }
			else { cout << "not found! " << endl; }
		}

		{
			timestart = clock();
			sort(c.begin(), c.end());
			cout << "sort(), seconds:" << SECONDS(clock()-timestart) << endl;
			timestart = clock();
			string *item = (string *)::bsearch(&target, (c.data()), c.size(), sizeof(string), compareString);
			//cout << "bsearch, seconds:" << SECONDS(clock()-timestart) << endl;
			cout << "bsearch, seconds:" << std::fixed << SECONDS(clock()-timestart) << endl; //std::fixed 不使用科学计数法
			if (nullptr != item) { cout << "found, " << *item << endl; }
			else { cout << "not found! " << endl; }
		}
		
		//result:
		//............test vector............
		//seconds: 0.259996
		//vector.size()= 1000000
		//vector.max_size()= 1073741823 //实际大小
		//vector.front()= 187158322
		//vector.back()= 128384975
		//vector.data()= 0xb6c95008
		//! 当size为1,000,000时插入时间为2.9s
		//! 当size为10,000,000时直接killed

		//target (0~2147483647): std::find(), seconds:0.017957
		//not found! 
		//sort(), seconds:1.26775
		//bsearch, seconds:0.000005
		//not found! 
	}

};

#include <list>
using std::list;

namespace test_list
{
	void test_list()
	{
		std::cout << "............test list............" << std::endl;
		list<string> c;

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
		} //for 

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "list.size()= " << c.size() << endl;
		cout << "list.max_size()= " << c.max_size() << endl;
		cout << "list.front()= " << c.front() << endl;
		cout << "list.back()= " << c.back() << endl;

		string target = get_a_target_string();
		{
			timestart = clock();
			auto item = find(c.begin(), c.end(), target);
			cout << "std::find(), seconds:" << SECONDS(clock()-timestart) << endl;
			if (c.end() != item) { cout << "found, " << *item << endl; }
			else { cout << "not found! " << endl; }
		}

		{
			timestart = clock();
			c.sort();
			cout << "sort(), seconds:" << SECONDS(clock()-timestart) << endl;
		}

		//result:
		//............test list............
		//seconds: 0.366951
		//list.size()= 1000000
		//list.max_size()= 357913941
		//list.front()= 180428938
		//list.back()= 429357853
		//target (0~2147483647): std::find(), seconds:0.022652
		//not found! 
		//sort(), seconds:1.29558
	}
};

#include <forward_list>

using std::forward_list;

namespace test_forward_list
{
	void test_forward_list()
	{
		std::cout << "............test forward list............" << std::endl;
		srand(time(nullptr));

		forward_list<string> c;
		char buf[10];
		clock_t timestart = clock();

		for (int i=0; i<1000000; ++i) {
			try {
				snprintf(buf, 10, "%d", rand());
				c.push_front(string(buf));
			}
			catch(exception &p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		} //for

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "forward_list.max_size()= " << c.max_size() << endl;
		string target = get_a_target_string();
		timestart = clock();
		auto item = std::find(c.begin(), c.end(), target);
		cout << "std::find(), seconds:" << SECONDS(clock()-timestart) << endl;
		if (c.end() != item) { cout << "found, " << *item << endl; }
		else { cout << "not found! " << endl; }

		{
			timestart = clock();
			c.sort();
			cout << "sort(), seconds:" << SECONDS(clock()-timestart) << endl;
		}
		//result:
		//............test forward list............
		//seconds: 0.333147
		//forward_list.max_size()= 536870911
		//target (0~2147483647): std::find(), seconds:0.044755
		//not found! 
		//sort(), seconds:1.54503
	}
};

#include <deque>

using std::deque;

namespace test_deque
{
	void test_deque()
	{
		std::cout << "............test deque............" << std::endl;
		deque<string> c;

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
		} //for 

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "deque.size()= " << c.size() << endl;
		cout << "deque.max_size()= " << c.max_size() << endl;
		cout << "deque.front()= " << c.front() << endl;
		cout << "deque.back()= " << c.back() << endl;

		string target = get_a_target_string();
		{
			timestart = clock();
			auto item = find(c.begin(), c.end(), target);
			cout << "std::find(), seconds:" << SECONDS(clock()-timestart) << endl;
			if (c.end() != item) { cout << "found, " << *item << endl; }
			else { cout << "not found! " << endl; }
		}

		{
			timestart = clock();
			sort(c.begin(), c.end());
			cout << "sort(), seconds:" << SECONDS(clock()-timestart) << endl;
		}
		//result:
			//............test deque............
			//seconds: 0.234153
			//deque.size()= 1000000
			//deque.max_size()= 1073741823
			//deque.front()= 180428938
			//deque.back()= 429357853
			//target (0~2147483647): std::find(), seconds:0.013567
			//not found! 
			//sort(), seconds:1.35966
	}
};

int main(int argc, char *argv[])
{
	//test_array::test_array();
	//test_vector::test_vector();
	//test_list::test_list();
	//test_forward_list::test_forward_list();
	test_deque::test_deque();
	return 0;
}







