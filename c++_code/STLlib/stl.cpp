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


/*
 * 说明：在ubuntu 14.04下RAND_MAX 为2,147,483,647
 * hash_set, hash_map 在ext目录下，很少用到
 * */

#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>

const long ASIZE = 500000L;
const long ELEMENT_SIZE = 1000000L;

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

		for (int i=0; i<ELEMENT_SIZE; ++i) {
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

		for (int i=0; i<ELEMENT_SIZE; ++i) {
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

		for (int i=0; i<ELEMENT_SIZE; ++i) {
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

		for (int i=0; i<ELEMENT_SIZE; ++i) {
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

#include <set>

using std::multiset;

namespace test_multi_set
{
	void set_multiset()
	{
		std::cout << "............test multiset............" << std::endl;
		multiset<string> c;

		char buf[10];
		clock_t timestart = clock();

		for (int i=0; i<ELEMENT_SIZE; ++i) {
			try {
				snprintf(buf, 10, "%d", rand()/10000);
				c.insert(string(buf));
			}
			catch(exception &p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		} //for 

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "multiset.size()= " << c.size() << endl;
		cout << "multiset.max_size()= " << c.max_size() << endl;
		
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
			auto item = c.find(target);
			cout << "find(), seconds:" << std::fixed << SECONDS(clock()-timestart) << endl;
			if (c.end() == item) {
				cout << "not found." << endl;
			}
			else {
				cout << "found, " << *item << endl;
			} // if 
		}

//result:
	//............test multiset............
	//seconds: 1.91099
	//multiset.size()= 1000000
	//multiset.max_size()= 214748364
	//target (0~2147483647): std::find(), seconds:0.01785
	//found, 12345
	//find(), seconds:0.000003
	//found, 12345
	}
};

#include <map>

using std::multimap;
using std::pair;

namespace test_multi_map
{
	void set_multimap()
	{
		std::cout << "............test set_multimap............" << std::endl;
		multimap<long, string> c;

		char buf[10];
		clock_t timestart = clock();

		for (int i=0; i<ELEMENT_SIZE; ++i) {
			try {
				snprintf(buf, 10, "%d", rand()/10000);
				//multimap 不能使用[]做insertion
				c.insert(pair<long, string>(i, buf));
			}
			catch(exception &p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		} //for 

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "multimap.size()= " << c.size() << endl;
		cout << "multimap.max_size()= " << c.max_size() << endl;
		long target = get_a_target_long();
		//{
			//timestart = clock();
			//error，pair对象没有重载operator==操作符，所以不能使用std::find算法进行查找
			//auto item = find(c.begin(), c.end(), target);
		//}

		{
			timestart = clock();
			auto item = c.find(target);
			cout << "find(), seconds:" << std::fixed << SECONDS(clock()-timestart) << endl;
			if (c.end() == item) {
				cout << "not found." << endl;
			}
			else {
				cout << "found, " << item->second << endl;
			} // if 
		}
	//result:		
	//............test set_multimap............
	//seconds: 0.807391
	//multimap.size()= 1000000
	//multimap.max_size()= 178956970
	//target (0~2147483647): find(), seconds:0.000006
	//found, 196384
	}
};

#include <unordered_set>

using std::unordered_multiset;

namespace test_unordred_multiset
{
	void test_unordred_multiset()
	{
		std::cout << "............test unorderedset............" << std::endl;

		srand(time(nullptr));

		unordered_multiset<string> c;
		char buf[10];
		clock_t timestart = clock();

		for (int i=0; i<ELEMENT_SIZE; ++i) {
			try {
				snprintf(buf, 10, "%d", rand()/1000);
				c.insert(string(buf));
			}
			catch(exception &p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		} // for

		
		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "unordered_multiset.size()= " << c.size() << endl;
		cout << "unordered_multiset.max_size()= " << c.max_size() << endl;
		cout << "unordered_multiset.bucket_count()= " << c.bucket_count() << endl;
		cout << "unordered_multiset.load_factor()= " << c.load_factor() << endl;
		cout << "unordered_multiset.max_load_factor()= " << c.max_load_factor() << endl;
		cout << "unordered_multiset.max_bucket_count()= " << c.max_bucket_count() << endl;

		for (int i=0; i<20; ++i) {
			cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";
		}

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
			auto item = c.find(target);
			cout << "find(), seconds:" << std::fixed << SECONDS(clock()-timestart) << endl;
			if (c.end() == item) {
				cout << "not found." << endl;
			}
			else {
				cout << "found, " << *item << endl;
			} // if 
		}
//result:
//............test unorderedset............
//seconds: 0.825236
//unordered_multiset.size()= 1000000
//unordered_multiset.max_size()= 357913941
//unordered_multiset.bucket_count()= 1056323
//unordered_multiset.load_factor()= 0.94668
//unordered_multiset.max_load_factor()= 1
//unordered_multiset.max_bucket_count()= 357913941
//bucket #0 has 2 elements.
//bucket #1 has 1 elements.
//bucket #2 has 1 elements.
//bucket #3 has 0 elements.
//bucket #4 has 2 elements.
//bucket #5 has 0 elements.
//bucket #6 has 0 elements.
//bucket #7 has 1 elements.
//bucket #8 has 0 elements.
//bucket #9 has 1 elements.
//bucket #10 has 3 elements.
//bucket #11 has 0 elements.
//bucket #12 has 1 elements.
//bucket #13 has 1 elements.
//bucket #14 has 0 elements.
//bucket #15 has 2 elements.
//bucket #16 has 1 elements.
//bucket #17 has 3 elements.
//bucket #18 has 4 elements.
//bucket #19 has 2 elements.
//target (0~2147483647): std::find(), seconds:0.098153
//not found! 
//find(), seconds:0.000001
//not found.
	}
};

#include <ext/slist>

namespace test_slist
{
	void test_slist()
	{
		std::cout << "............test slist............" << std::endl;

		srand(time(nullptr));

		__gnu_cxx::slist<string> c;
		char buf[10];
		clock_t timestart = clock();

		for (int i=0; i<ELEMENT_SIZE; ++i) {
			try {
				snprintf(buf, 10, "%d", rand()/1000);
				c.push_front(string(buf));
			}
			catch(exception &p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		} // for

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		
//result:
//............test unorderedset............
//seconds: 0.291623
	}

}

#include <map>

using std::map;
using std::pair;

namespace test_map
{
	void test_map()
	{
		std::cout << "............test map............" << std::endl;
		map<long, string> c;

		char buf[10];
		clock_t timestart = clock();

		for (int i=0; i<ELEMENT_SIZE; ++i) {
			try {
				snprintf(buf, 10, "%d", rand()/10000);
				//multimap 不能使用[]做insertion，但是mapqueue是可以使用
				c[i] = buf;
			}
			catch(exception &p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		} //for 

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "map.size()= " << c.size() << endl;
		cout << "map.max_size()= " << c.max_size() << endl;
		long target = get_a_target_long();
		{
			timestart = clock();
			auto item = c.find(target);
			cout << "find(), seconds:" << std::fixed << SECONDS(clock()-timestart) << endl;
			if (c.end() == item) {
				cout << "not found." << endl;
			}
			else {
				cout << "found, " << item->second << endl;
			} // if 
		}
//result:
//............test map............
//seconds: 1.01845
//map.size()= 1000000
//map.max_size()= 178956970
//target (0~2147483647): find(), seconds:0.000005
//found, 136033
	}
};

#include <set>

using std::set;

namespace test_set
{
	void test_set()
	{
		std::cout << "............test set............" << std::endl;
		set<string> c;

		char buf[10];
		clock_t timestart = clock();

		for (int i=0; i<ELEMENT_SIZE; ++i) {
			try {
				snprintf(buf, 10, "%d", rand()/10000);
				c.insert(string(buf));
			}
			catch(exception &p) {
				cout << "i=" << i << " " << p.what() << endl;
				abort();
			}
		} //for 

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "multiset.size()= " << c.size() << endl;
		cout << "multiset.max_size()= " << c.max_size() << endl;
		
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
			auto item = c.find(target);
			cout << "find(), seconds:" << std::fixed << SECONDS(clock()-timestart) << endl;
			if (c.end() == item) {
				cout << "not found." << endl;
			}
			else {
				cout << "found, " << *item << endl;
			} // if 
		}

//result:
//............test set............
//seconds: 1.61553
//multiset.size()= 212740
//multiset.max_size()= 214748364
//target (0~2147483647): std::find(), seconds:0.015326
//found, 23456
//find(), seconds:0.000003
//found, 23456
	}
};

int main(int argc, char *argv[])
{
	//test_array::test_array();
	//test_vector::test_vector();
	//test_list::test_list();
	//test_forward_list::test_forward_list();
	//test_deque::test_deque();
	//test_multi_set::set_multiset();
	//test_multi_map::set_multimap();
	//test_unordred_multiset::test_unordred_multiset();
	//test_slist::test_slist();
	//test_map::test_map();
	test_set::test_set();
	return 0;
}



