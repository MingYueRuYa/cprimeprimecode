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

#include <cstring>

// 一下测试MyString是为了测试containers with moveable elements
class MyString {
public:
	static size_t DCtor;	// default-ctor
	static size_t Ctor;		// ctor
	static size_t CCtor;	// copy ctor
	static size_t CAsgn;	// copy assignment
	static size_t MCtor;	// move ctor
	static size_t MAsgn;	// move-asgn
	static size_t Dtor;		// dtor

public:
	// default ctor
	MyString() : _data(NULL), _len(0) { ++DCtor; }

	// ctor
	MyString(const char *p) : _len(strlen(p)) {
		++Ctor;
		_init_data(p);
	}

	// copy ctor
	MyString(const MyString &str) : _len(str._len) {
		++CCtor;
		_init_data(str._data);
	}

	MyString(MyString &&str) noexcept : _data(str._data), _len(str._len) {
		++MCtor;
		str._len  = 0;
		str._data = NULL;
	}

	MyString &operator =(const MyString &str) {
		++CAsgn;
		if (this == &str) {
			return *this;	
		}

		if (_data) {
			delete _data;
			_data = NULL;
		}

		_len = str._len;
		_init_data(str._data);
	}

	MyString &operator =(MyString &&str) {
		++MAsgn;
		if (this == &str) {
			return *this;	
		}

		if (_data) {
			delete _data;
			_data = NULL;
		}
		_len  = str._len;
		_data = str._data;
		str._len  = 0;
		str._data = NULL;
	}

	virtual ~MyString() {
		++Dtor;
		if (NULL != _data) {
			delete _data;
			_data = NULL;
		}
	}

	bool
	operator <(const MyString &rhs) const
	{
		// 借用string比较大小
		return std::string(this->_data) < std::string(rhs._data);
	}

	bool
	operator ==(const MyString &rhs) const
	{
		// 借用string比较大小
		return std::string(this->_data) == std::string(rhs._data);
	}

	char *get() const { return _data; }


private:
	char *_data;
	size_t _len;

	void _init_data(const char *s) {
		_data = new char[_len+1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

};

size_t MyString::DCtor = 0;
size_t MyString::Ctor  = 0;
size_t MyString::CCtor = 0;
size_t MyString::CAsgn = 0;
size_t MyString::MCtor = 0;
size_t MyString::MAsgn = 0;
size_t MyString::Dtor  = 0;

class MyStrNoMove {
public:
	static size_t DCtor;	// default-ctor
	static size_t Ctor;		// ctor
	static size_t CCtor;	// copy ctor
	static size_t CAsgn;	// copy assignment
	static size_t MCtor;	// move ctor
	static size_t MAsgn;	// move-asgn
	static size_t Dtor;		// dtor

public:
	// default ctor
	MyStrNoMove() : _data(NULL), _len(0) { ++DCtor; }

	// ctor
	MyStrNoMove(const char *p) : _len(strlen(p)) {
		++Ctor;
		_init_data(p);
	}

	// copy ctor
	MyStrNoMove(const MyStrNoMove &str) : _len(str._len) {
		++CCtor;
		_init_data(str._data);
	}

	MyStrNoMove &operator =(const MyStrNoMove &str) {
		++CAsgn;
		if (this == &str) {
			return *this;	
		}

		if (_data) {
			delete _data;
			_data = NULL;
		}

		_len = str._len;
		_init_data(str._data);
	}

	virtual ~MyStrNoMove() {
		++Dtor;
		if (NULL != _data) {
			delete _data;
			_data = NULL;
		}
	}

	bool
	operator <(const MyStrNoMove &rhs) const
	{
		// 借用string比较大小
		return std::string(this->_data) < std::string(rhs._data);
	}

	bool
	operator ==(const MyStrNoMove &rhs) const
	{
		// 借用string比较大小
		return std::string(this->_data) == std::string(rhs._data);
	}

	char *get() const { return _data; }


private:
	char *_data;
	size_t _len;

	void _init_data(const char *s) {
		_data = new char[_len+1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

};

size_t MyStrNoMove::DCtor = 0;
size_t MyStrNoMove::Ctor  = 0;
size_t MyStrNoMove::CCtor = 0;
size_t MyStrNoMove::CAsgn = 0;
size_t MyStrNoMove::MCtor = 0;
size_t MyStrNoMove::MAsgn = 0;
size_t MyStrNoMove::Dtor  = 0;

#include <list>
#include <forward_list>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>

using std::max;
using std::min;
using std::string;
using std::hash;

namespace std
{

template<>
struct hash<MyString>
{
    size_t operator()(const MyString& s) const noexcept
    {
        return hash<string>()(string(s.get()));
    }
};

};

namespace test_misc
{
bool strLonger(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

void test_misc()
{
	cout << "\ntest_misc()..................\n";
	// 以下这些都是标准库的众多容器的max_size()计算方式
	cout << size_t(-1) << endl;	// 4294967295
	cout << size_t(-1)/sizeof(long) << endl;	// 1073741823
	cout << size_t(-1)/sizeof(string) << endl;	// 1073741823
 	cout << size_t(-1)/sizeof(std::_List_node<string>) << endl;	// 357913941
 	cout << size_t(-1)/sizeof(std::_Fwd_list_node<string>) 
		 << endl; // 536870911

	cout << "RAND_MAX=" << RAND_MAX << endl;	// RAND_MAX=2147483647

    cout << std::min( {2, 5, 8, 9, 45, 0, 81} ) << endl;	// 0
    cout << std::max( {2, 5, 8, 9, 45, 0, 81} ) << endl;	// 81

    std::vector<int> vint {2, 5, 8, 9, 45, 0, 81};

    cout << "max of zoo and hello:"
         << max(string("zoo"), string("hello")) << endl;	// zoo

    cout << "max of zoo and hello:"
         << max(string("zoo"), string("hello"), strLonger) << endl;	// hello

    cout << std::hash<MyString>()(MyString("Ace")) << endl;	// 1765813650
    cout << std::hash<MyString>()(MyString("Stacy")) << endl;	// 2790324277
    cout << "MyString(zoo) < MyString(hello) ==> "
         << (MyString("zoo") < MyString("hello")) << endl;	// 0
    cout << "MyString(zoo) == MyString(hello) ==> "
         << (MyString("zoo") == MyString("hello")) << endl;	// 0
    cout << "MyStrNoMove(zoo) < MyStrNoMove(hello) ==> "
         << (MyStrNoMove("zoo") < MyStrNoMove("hello")) << endl;	// 0
    cout << "MyStrNoMove(zoo) == MyStrNoMove(hello) ==> "
         << (MyStrNoMove("zoo") == MyStrNoMove("hello")) << endl;	// 0

}

};

#include <typeinfo>

namespace test_moveable
{

template<typename T>
void output_static_data(const T&str)
{
	cout << typeid(str).name() << "  -- " << endl;
	cout << "CCtor="   << T::Ctor
		 << " MCtor="  << T::MCtor
		 << " CAsgn="  << T::CAsgn
		 << " MAsgn="  << T::MAsgn
		 << " Dtor="   << T::DCtor
		 << " Ctor="   << T::Ctor
		 << " DCtor="  << T::DCtor
		 << endl;
}

template<typename M, typename NM>
void test_moveable(M c1, NM c2, long &value)
{
	char buf[10];

	// 测试move
	cout << "\n\ntest, with moveable elements" << endl;
	typedef typename std::iterator_traits<typename M::iterator>::value_type \
		V1Type;	


}

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

		cout << "seconds: " << (double)(clock()-timestart)/CLOCKS_PER_SEC 
             << endl;
		cout << "array.size()= " << c.size() << endl;
		cout << "array.front()= " << c.front() << endl;
		cout << "array.back()= " << c.back() << endl;
		cout << "array.data()= " << c.data() << endl;

		long target = get_a_target_long();
		timestart = clock();
		::qsort(c.data(), ASIZE, sizeof(long), compareLongs);
		long *item = (long *)::bsearch(&target
                                        , (c.data())
                                        , ASIZE 
                                        , sizeof(long)
                                        , compareLongs);
		cout << "qsort()+bsearch(), seconds: " 
             << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;

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
		cout << "seconds: " 
             << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "vector.size()= " << c.size() << endl;
		cout << "vector.max_size()= " << c.max_size() << endl;
		cout << "vector.front()= " << c.front() << endl;
		cout << "vector.back()= " << c.back() << endl;
		cout << "vector.data()= " << c.data() << endl;

		string target = get_a_target_string();
		{
			timestart = clock();
			auto item = find(c.begin(), c.end(), target);
			cout << "std::find(), seconds:" 
                 << SECONDS(clock()-timestart) << endl;
			if (c.end() != item) { cout << "found, " << *item << endl; }
			else { cout << "not found! " << endl; }
		}

		{
			timestart = clock();
			sort(c.begin(), c.end());
			cout << "sort(), seconds:" << SECONDS(clock()-timestart) << endl;
			timestart = clock();
			string *item = (string *)::bsearch(&target
                                                , (c.data())
                                                , c.size()
                                                , sizeof(string)
                                                , compareString);
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

		cout << "seconds: " 
             << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "list.size()= " << c.size() << endl;
		cout << "list.max_size()= " << c.max_size() << endl;
		cout << "list.front()= " << c.front() << endl;
		cout << "list.back()= " << c.back() << endl;

		string target = get_a_target_string();
		{
			timestart = clock();
			auto item = find(c.begin(), c.end(), target);
			cout << "std::find(), seconds:" 
                 << SECONDS(clock()-timestart) << endl;
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

		cout << "seconds: " 
			 << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "multimap.size()= " << c.size() << endl;
		cout << "multimap.max_size()= " << c.max_size() << endl;
		long target = get_a_target_long();
		
		//{
			//timestart = clock();
			//error，pair对象没有重载operator==操作符
			//，所以不能使用std::find算法进行查找
			//auto item = find(c.begin(), c.end(), target);
		//}

		{
			timestart = clock();
			auto item = c.find(target);
			cout << "find(), seconds:" 
				 << std::fixed << SECONDS(clock()-timestart) << endl;
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

		
		cout << "seconds: " 
			 << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "unordered_multiset.size()= " << c.size() << endl;
		cout << "unordered_multiset.max_size()= " << c.max_size() << endl;
		cout << "unordered_multiset.bucket_count()= " 
			 << c.bucket_count() << endl;
		cout << "unordered_multiset.load_factor()= " 
			 << c.load_factor() << endl;
		cout << "unordered_multiset.max_load_factor()= " 
			 << c.max_load_factor() << endl;
		cout << "unordered_multiset.max_bucket_count()= "
		     << c.max_bucket_count() << endl;

		for (int i=0; i<20; ++i) {
			cout << "bucket #" << i << " has " 
				 << c.bucket_size(i) << " elements.\n";
		}

		string target = get_a_target_string();
		{
			timestart = clock();
			auto item = find(c.begin(), c.end(), target);
			cout << "std::find(), seconds:" 
				 << SECONDS(clock()-timestart) << endl;
			if (c.end() != item) { cout << "found, " << *item << endl; }
			else { cout << "not found! " << endl; }
		}

		{
			timestart = clock();
			auto item = c.find(target);
			cout << "find(), seconds:" 
				 << std::fixed << SECONDS(clock()-timestart) << endl;
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

		cout << "seconds: " 
			 << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		
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

		cout << "seconds: " 
			 << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "map.size()= " << c.size() << endl;
		cout << "map.max_size()= " << c.max_size() << endl;
		long target = get_a_target_long();
		{
			timestart = clock();
			auto item = c.find(target);
			cout << "find(), seconds:" 
				 << std::fixed << SECONDS(clock()-timestart) << endl;
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

		cout << "seconds: " 
			 << (double)(clock()-timestart)/CLOCKS_PER_SEC << endl;
		cout << "multiset.size()= " << c.size() << endl;
		cout << "multiset.max_size()= " << c.max_size() << endl;
		
		string target = get_a_target_string();
		{
			timestart = clock();
			auto item = find(c.begin(), c.end(), target);
			cout << "std::find(), seconds:" 
				 << SECONDS(clock()-timestart) << endl;
			if (c.end() != item) { cout << "found, " << *item << endl; }
			else { cout << "not found! " << endl; }
		}

		{
			timestart = clock();
			auto item = c.find(target);
			cout << "find(), seconds:" 
				 << std::fixed << SECONDS(clock()-timestart) << endl;
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

#include <bits/stl_tree.h>
#include <bits/stl_function.h>
using std::_Rb_tree;
using std::_Identity;
using std::less;

/*
 * 直接使用rb_tree底层的数据结构
 * */
namespace test_rb_tree
{

void test_rb_tree()
{
	_Rb_tree<int, int, _Identity<int>, less<int>> itree;
	cout << itree.empty() << endl;	// 1
	cout << itree.size() << endl;	// 0
	itree._M_insert_unique(3);
	itree._M_insert_unique(8);
	itree._M_insert_unique(5);
	itree._M_insert_unique(9);
	itree._M_insert_unique(13);
	itree._M_insert_unique(5);	//no effect, since using _M_insert_equal().

	cout << itree.empty() << endl;	// 0
	cout << itree.size() << endl;	// 5
	cout << itree.count(5) << endl;	// 1

	itree._M_insert_equal(5);
	itree._M_insert_equal(5);
	cout << itree.size() << endl;	// 7
	cout << itree.count(5) << endl;	// 3
}

};


#include <iostream>
#include <iterator>
#include <typeinfo>
#include <unordered_set>
#include <unordered_map>
//#include <unordered_multiset>
//#include <unordered_multimap>

using std::unordered_set;
using std::unordered_map;
using std::unordered_multiset;
using std::unordered_multimap;

using std::iterator_traits;
using std::input_iterator_tag;
using std::output_iterator_tag;
using std::forward_iterator_tag;
using std::random_access_iterator_tag;
using std::bidirectional_iterator_tag;
using std::istream_iterator;
using std::ostream_iterator;

namespace display_category
{
void _display_catetory(random_access_iterator_tag)	{
	cout << "random_access_iterator_tag" << endl;
}

void _display_catetory(bidirectional_iterator_tag)	{
	cout << "bidirectional_iterator_tag" << endl;
}

void _display_catetory(forward_iterator_tag)	{
	cout << "forward_iterator_tag" << endl;
}

void _display_catetory(output_iterator_tag)	{
	cout << "output_iterator_tag" << endl;
}

void _display_catetory(input_iterator_tag)	{
	cout << "input_iterator_tag" << endl;
}

template <typename I>
void display_category(I itr) {
	typename iterator_traits<I>::iterator_category category;
	_display_catetory(category);
	cout << "typeid(itr).name()=" << typeid(itr).name() << endl;
}

void test_display_iterator_category()
{
	display_category(array<int, 10>::iterator());
	cout << "-------------array-----------" << endl;
	display_category(vector<int>::iterator());
	cout << "-------------vector-----------" << endl;
	display_category(list<int>::iterator());
	cout << "--------------list------------" << endl;
	display_category(forward_list<int>::iterator());
	cout << "---------forward_list---------" << endl;
	display_category(deque<int>::iterator());
	cout << "------------deque-------------" << endl;


	display_category(set<int>::iterator());
	cout << "-------------set---------------" << endl;
	display_category(map<int, int>::iterator());
	cout << "-------------map--------------" << endl;
	display_category(multiset<int>::iterator());
	cout << "-----------multiset-----------" << endl;
	display_category(multimap<int, int>::iterator());
	cout << "-----------multimap-----------" << endl;
	display_category(unordered_set<int>::iterator());
	cout << "---------unordered_set---------" << endl;
	display_category(unordered_map<int, int>::iterator());
	cout << "---------unordered_map--------" << endl;
	display_category(unordered_multiset<int>::iterator());
	cout << "------unordered_multiset------" << endl;
	display_category(unordered_multimap<int, int>::iterator());
	cout << "------unordered_multimap------" << endl;

	display_category(istream_iterator<int>());
	cout << "------istream_iterator--------" << endl;
	display_category(ostream_iterator<int>(cout, ""));
	cout << "------ostream_iterator--------" << endl;
//result:
	//random_access_iterator_tag
	//typeid(itr).name()=Pi
	//-------------array-----------
	//random_access_iterator_tag
	//typeid(itr).name()=N9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE
	//-------------vector-----------
	//bidirectional_iterator_tag
	//typeid(itr).name()=St14_List_iteratorIiE
	//--------------list------------
	//forward_iterator_tag
	//typeid(itr).name()=St18_Fwd_list_iteratorIiE
	//---------forward_list---------
	//random_access_iterator_tag
	//typeid(itr).name()=St15_Deque_iteratorIiRiPiE
	//------------deque-------------
	//bidirectional_iterator_tag
	//typeid(itr).name()=St23_Rb_tree_const_iteratorIiE
	//-------------set---------------
	//bidirectional_iterator_tag
	//typeid(itr).name()=St17_Rb_tree_iteratorISt4pairIKiiEE
	//-------------map--------------
	//bidirectional_iterator_tag
	//typeid(itr).name()=St23_Rb_tree_const_iteratorIiE
	//-----------multiset-----------
	//bidirectional_iterator_tag
	//typeid(itr).name()=St17_Rb_tree_iteratorISt4pairIKiiEE
	//-----------multimap-----------
	//forward_iterator_tag
	//typeid(itr).name()=NSt8__detail14_Node_iteratorIiLb1ELb0EEE
	//---------unordered_set---------
	//forward_iterator_tag
	//typeid(itr).name()=NSt8__detail14_Node_iteratorISt4pairIKiiELb0ELb0EEE
	//---------unordered_map--------
	//forward_iterator_tag
	//typeid(itr).name()=NSt8__detail14_Node_iteratorIiLb1ELb0EEE
	//------unordered_multiset------
	//forward_iterator_tag
	//typeid(itr).name()=NSt8__detail14_Node_iteratorISt4pairIKiiELb0ELb0EEE
	//------unordered_multimap------
	//input_iterator_tag
	//typeid(itr).name()=St16istream_iteratorIicSt11char_traitsIcEiE
	//------istream_iterator--------
	//output_iterator_tag
	//typeid(itr).name()=St16ostream_iteratorIicSt11char_traitsIcEE
	//------ostream_iterator--------
}

};

#include <algorithm>
#include <functional>
#include <iostream>

using std::cout;
using std::endl;

namespace test_algorithm
{

namespace test_accumulate
{
int myfunc(int x, int y) { return x+2*y; }

struct myclass {
	int operator() (int x, int y) { return x+2*y; }
} myobj;

void test_accumulate()
{
	cout << "test_accumulate()....... \n";
	int init = 100;

	int nums[] = {10, 20, 30};

	cout << "using default accumulate: ";
	cout << std::accumulate(nums, nums+3, init) << endl;	//160
	
	cout << "using funtional's minus:";
	cout << std::accumulate(nums, nums+3, init, std::minus<int>()); //40
	cout << endl;

	cout << "using custom funtion:";
	cout << std::accumulate(nums, nums+3, init, myfunc); //220
	cout << endl;

	cout << "using custom object:";
	cout << std::accumulate(nums, nums+3, init, myclass()); //280
	cout << endl;
	//result:
		//test_accumulate()....... 
		//using default accumulate: 160
		//using funtional's minus:40
		//using custom funtion:220
		//using custom object:220
}
};

namespace test_for_each
{

void myfunc(int i) { cout << " " << i; } 

struct myclass {
	void operator() (int i) { cout << " " << i; }
} myobj;

void test_for_each()
{

	cout << "\ntest_for_each()...................\n";

	vector<int> myvec;
	myvec.push_back(10);
	myvec.push_back(20);
	myvec.push_back(30);

	cout << "test my custom function:" << endl;
	for_each(myvec.begin(), myvec.end(), myfunc);	
	cout << endl;

	cout << "test my custom function object:" << endl;
	for_each(myvec.begin(), myvec.end(), myobj);	
	cout << endl;

	for (const auto &elem : myvec) {
		cout << elem << " ";
	}
	cout << endl;

//result:
	//test_for_each()...................
	//test my custom function:
	// 10 20 30
	//test my custom function object:
	// 10 20 30
	//10 20 30 
}
};

using std::sort;

namespace test_sort
{
bool myfunc(int x, int y) { return x < y; }

struct myclass {
	bool operator() (int x, int y) {
		return x < y;
	}
}myobj;

void test_sort()
{
	cout << "test_sort()............\n";

	int myints[] = {32, 71, 12, 45, 26, 80, 53, 33};
	vector<int> myvec(myints, myints+8);

	// using default comparison (operator <):
	sort(myvec.begin(), myvec.begin()+4);
	// (12 32 45 74) 26 80 53 33

	// using function as comp
	sort(myvec.begin()+4, myvec.end(), myfunc);
	// 12 32 45 74 (26 33 53 80)

	// using object as comp
	sort(myvec.begin()+4, myvec.end(), myobj);
	// 12 32 45 74 (26 33 53 80)

	sort(myvec.rbegin(), myvec.rend());
	// 80 71 53 45 33 32 16 12

	sort(myvec.begin(), myvec.end(), std::less<int>());
	// 12 16 32 33 45 53 71 80

	sort(myvec.begin(), myvec.end(), std::greater<int>());
	// 80 71 53 45 33 32 16 12
}
};

};

namespace iterator_adapter
{

template <typename T>
struct display : public std::unary_function<T, T>
{
	T operator() (const T& t)
	{
		cout << t << " ";
		return t;
	}
};

void test_insert_iterator()
{
	int intarray[] = {10, 20, 30, 40, 50, 60, 70};
	vector<int> myvec(7);
	std::copy(std::begin(intarray), std::end(intarray), myvec.begin());
	std::for_each(myvec.begin(), myvec.end(), display<int>());
	// 10 20 30 40 50 60 70 
	cout << endl;

	vector<int>::iterator itr = myvec.begin();
	std::advance(itr, 3);
	// insert iterator 会自动调用容器的insert方法
	std::copy(std::begin(intarray), std::end(intarray)
			, std::inserter(myvec, itr));
	std::for_each(myvec.begin(), myvec.end(), display<int>());
	cout << endl;
}

void test_ostream_iterator()
{
	int intarray[] = {10, 20, 30, 40, 50, 60, 70};
	std::ostream_iterator<int> out_it(std::cout, ",");
	std::copy(std::begin(intarray), std::end(intarray), out_it);
}

void test_istream_iterator()
{
	std::ostream_iterator<int> out_it(std::cout, ",");
	double val1, val2;
	std::cout << "Please insert two values:";
	std::istream_iterator<double> eos;	// end-of-stream iterator
	std::istream_iterator<double> iit(std::cin);
	if (iit != eos) {
		val1 = *iit;
	}

	++iit;	
	if (iit != eos) {
		val2 = *iit;
	}

	std::cout << val1 << "*" << val2 << "=" << (val1*val2) << endl;

	vector<double> myvec;
	cout << "Please insert another data:" << endl;
	std::istream_iterator<double> iit2(std::cin);
	std::copy(iit2, eos, std::inserter(myvec, myvec.begin()));
	std::for_each(myvec.begin(), myvec.end(), display<int>());
}

};

#include <functional>

using std::hash;

namespace test_hash_function
{

//hash_val 可能现在的stl版本没有纳入进来，所以把source code直接照搬过来
template <typename T>
inline void hash_combine(size_t &seed, const T& val)
{
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T>
inline void hash_val(size_t &seed, const T& val)
{
	hash_combine(seed, val);
}

template <typename T, typename... Types>
inline void hash_val(size_t &seed, const T&val, const Types&... args)
{
	hash_combine(seed, val);
	// recursive call hash_val
	hash_val(seed, args...);
}

template <typename... Types>
inline size_t hash_val(const Types&... args)
{
	size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}

class Customer
{
public:
	Customer(string first_name, string last_name, int age)
		: mfirst_name(first_name), mlast_name(last_name), mage(age)
	{}

	Customer & operator=(const Customer& customer) = default;

	bool operator==(const Customer& customer) const
	{
		return (mfirst_name == customer.mfirst_name) 
				&& (mlast_name == customer.mlast_name)
				&& (mage == customer.mage);
	}

public:
	string 	mfirst_name;
	string	mlast_name;
	int 	mage;

};

class CustomHash
{
public:
	size_t operator() (const Customer& customer) const {
		return hash_val(customer.mfirst_name
						, customer.mlast_name
						, customer.mage);
	}
};

void test_hash_function()
{
// 自定义类型放到set对象里面时，需要自定义hash function
// 以及需要重载 operator== 操作符

	 CustomHash cushash;
	 cout << "bucket position of Ace=" 
	 	 << cushash(Customer("Ace", "Hou", 1L)) % 11 << endl;	// 2
			
	cout << "bucket position of Sabri=" 
		 << cushash(Customer("Sabri", "Hou", 2L)) % 11 << endl;	// 4

	cout << "bucket position of Stacy=" 
		 << cushash(Customer("Stacy", "Chen", 3L)) % 11 << endl; // 10

	cout << "bucket position of Mike=" 
		 << cushash(Customer("Mike", "Tseng", 4L)) % 11 << endl; // 2

	cout << "bucket position of Paili=" 
		 << cushash(Customer("Light", "Shiau", 5L)) % 11 << endl; // 3

	cout << "bucket position of Shally=" 
		 << cushash(Customer("Shally", "Hwung", 6L)) % 11 << endl; // 10

	std::unordered_set<Customer, CustomHash> set3;
	set3.insert(Customer("Ace", "Hou", 1L));
	set3.insert(Customer("Sabri", "Hou", 2L));
	set3.insert(Customer("Stacy", "Chen", 3L));
	set3.insert(Customer("Mike", "Tseng", 4L));
	set3.insert(Customer("Light", "Shiau", 5L));
	set3.insert(Customer("Shally", "Hwung", 6L));

	cout << "set3 current bucket_count:"
		 << set3.bucket_count() << endl;

	for (size_t i=0; i<set3.bucket_count(); ++i) {
		cout << "bucket #" << i << " has " << set3.bucket_size(i) 
			 << " elements." << endl;
	}
	
	// result:
		// bucket #0 has 0 elements.
		// bucket #1 has 0 elements.
		// bucket #2 has 2 elements.
		// bucket #3 has 1 elements.
		// bucket #4 has 1 elements.
		// bucket #5 has 0 elements.
		// bucket #6 has 0 elements.
		// bucket #7 has 0 elements.
		// bucket #8 has 0 elements.
		// bucket #9 has 0 elements.
		// bucket #10 has 2 elements.
}

};

#include <complex>
#include <tuple>

using std::complex;
using std::tuple;
using std::get;

namespace test_tuple
{
void test_tuple()
{
	cout << "string, sizeof=" << sizeof(string) << endl;	//4
	cout << "double, sizeof=" << sizeof(double) << endl;	//8
	cout << "float, sizeof="  << sizeof(float)  << endl;	//4
	cout << "complex<double>, sizeof=" 
		 << sizeof(complex<double>) << endl;	// 16
	
	//tuples
	tuple<string, int, int, complex<double> >t;
	cout << "tuple<string, int, int, complex<double> > sizeof=" 
		 << sizeof(t) << endl;	//28

	//create and initialize a tuple explicitly
	tuple<int, float, string>t1(41, 6.3, "nico");
	cout << "t1:" << get<0>(t1) << " " 
				  << get<1>(t1) << " " 
				  << get<2>(t1) << endl;
	// t1:41 6.3 nico

	auto t2 = std::make_tuple(22, 44, "stacy");

	get<1>(t1) = get<1>(t2);

	cout << "t1:" << get<0>(t1) << " " 
				  << get<1>(t1) << " " 
				  << get<2>(t1) << endl;
	// t1:41 44 nico

	if (t1 < t2) {	// compares value for value
		cout << "t1 < t2" << endl;
	} else {
		cout << "t1 > t2" << endl;
	}
	// t1 > t2

	t1 = t2;
	cout << "t1:" << get<0>(t1) << " " 
				  << get<1>(t1) << " " 
				  << get<2>(t1) << endl;

	tuple<int, float, string> t3(77, 1.10, "more light");
	int i1;
	float f1;
	string s1;

	tie(i1, f1, s1) = t3;	// assigns values of t to i, f, s

	cout << "i1 " << i1 << " f1 " << f1 << " s1 " << s1 << endl;
	// 77 1.1 more light

	typedef tuple<int, float, string> TupleType;
	cout << std::tuple_size<TupleType>::value << endl;	// 3
	std::tuple_element<1, TupleType>::type f2 = 1.0;	// yield float 

	typedef std::tuple_element<1, TupleType>::type T;
}
};

#include <type_traits>

namespace test_type_traits
{

template<typename T>
void type_traits_output(const T&x)
{
	cout << "\ntype traits for type: " << typeid(T).name() << endl;
	cout << "is_void\t" << std::is_void<T>::value << endl;
	cout << "is_integral\t" << std::is_integral<T>::value << endl;
	cout << "is_floating_point\t" << std::is_floating_point<T>::value << endl;
	cout << "is_arithmetic\t" << std::is_arithmetic<T>::value << endl;
	cout << "is_signed\t" << std::is_signed<T>::value << endl;
	cout << "is_unsigned\t" << std::is_unsigned<T>::value << endl;
	cout << "is_const\t" << std::is_signed<T>::is_const << endl;
	cout << "is_volatile\t" << std::is_volatile<T>::value << endl;
	cout << "is_class\t" << std::is_class<T>::value << endl;
	cout << "is_function\t" << std::is_function<T>::value << endl;
	cout << "is_reference\t" << std::is_reference<T>::value << endl;
	cout << "is_lvalue_reference\t" 
		 << std::is_lvalue_reference<T>::value << endl;
	cout << "is_rvalue_reference\t" 
		 << std::is_rvalue_reference<T>::value << endl;
	cout << "is_pointer\t" << std::is_pointer<T>::value << endl;
	cout << "is_member_pointer\t" << std::is_member_pointer<T>::value << endl;
	cout << "is_member_object_pointer\t" 
		 << std::is_member_object_pointer<T>::value << endl;
	cout << "is_member_function_pointer\t" 
		 << std::is_member_function_pointer<T>::value << endl;
	cout << "is_fundamental\t" << std::is_fundamental<T>::value << endl;
	cout << "is_scalar\t" << std::is_scalar<T>::value << endl;
	cout << "is_object\t" << std::is_object<T>::value << endl;
	cout << "is_compound\t" << std::is_compound<T>::value << endl;
}

void test_type_traits()
{
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
	//test_set::test_set();
	//test_rb_tree::test_rb_tree();
	//display_category::test_display_iterator_category();	
	//test_algorithm::test_accumulate::test_accumulate();
	//test_algorithm::test_for_each::test_for_each();
	//iterator_adapter::test_insert_iterator();
	//iterator_adapter::test_ostream_iterator();
	//iterator_adapter::test_istream_iterator();
	//test_hash_function::test_hash_function();
	//test_tuple::test_tuple();
    test_misc::test_misc();
	return 0;
}

