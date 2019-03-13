/****************************************************************************
**
** Copyright (C) 2019 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#ifndef lvalue_h
#define lvalue_h

#include <string>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <map>
#include <unordered_map>
#include <bitset>

using std::map;
using std::vector;
using std::string;

#ifndef _MSC_VER
#include <cxxabi.h>
#endif // _MSC_VER

namespace LValue{

template <typename T>
std::string type_name()
{
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void *)> own(
#ifndef __GNUC__
		nullptr,
#else
		abi::__cxa_demangle(typeid(TR).name()), nullptr, nullptr, nullptr),
#endif // __GNUC__
		std::free);

	std::string r = own != nullptr ? own.get() : typeid(TR).name();

	if (std::is_const<TR>::value) {
		r += " const";
	}

	if (std::is_volatile<TR>::value) {
		r += " volatile";
	}

	if (std::is_lvalue_reference<T>::value) {
		r += " &";
	}
	else if (std::is_rvalue_reference<T>::value) {
		r += " &&";
	}
	
	return r;
}

template <typename T>
void Func(T&& t)
{
	std::cout << type_name<T>() << std::endl;
}

void TestRValueFun()
{
	std::string str = "Test";
	
	Func(str);
	Func(std::move(str));
}

class TestCopyCon{
public:
	TestCopyCon(int id) : m_ptr(new int(id))
	{ cout << "constructor " << *m_ptr << endl; }

	TestCopyCon(const TestCopyCon &rhs) : m_ptr(new int(*rhs.m_ptr))
	{ cout << "copy constructor" << endl; }

	TestCopyCon(TestCopyCon &&rhs) : m_ptr(rhs.m_ptr)
	{ 
		rhs.m_ptr = nullptr;
		cout << "move constructor" << endl; 
	}

	~TestCopyCon() 
	{ 
		cout << "~dtor " << endl; 

		if (nullptr == m_ptr) { return; }

		delete m_ptr;
		m_ptr = nullptr;
	}

private:
	int *m_ptr;
};

TestCopyCon GetTestCopyCon(bool ret)
{
	TestCopyCon a(1);
	TestCopyCon b(2);
	if (ret) {
		return a;
	} else {
		return a;
	}
}

void TestCopyCon01()
{
	TestCopyCon con3 = GetTestCopyCon(true);
}

template <typename T>
void PrintT(T &t)
{
	cout << "left value" << endl;
}

template <typename T>
void PrintT(T &&t)
{
	cout << "right value" << endl;
}

template <typename T>
void TestForward(T && t)
{
	PrintT(t);
	PrintT(std::forward<T>(t));
	PrintT(std::move(t));
}

void TestForwardFun()
{
	TestForward(1);
	int x = 1;
	TestForward(x);
	TestForward(std::forward<int>(x));
}

// 万能的函数包装器，并不能实现函数的参数不同问题
template <class Function, class... Args>
inline auto FuncWrapper(Function && f, Args && ... args) -> decltype(f(std::forward<Args>(args)...))
{
	return f(std::forward<Args>(args)...);
}

void test0()
{
	cout << "void" << endl;
}

int test1()
{
	return 1;
}

int test2(int x)
{
	return x;
}

string test3(string s1, string s2)
{
	return s1+s2;
}

void TestFuncWrapperFunc()
{
	FuncWrapper(test0);

	int value = FuncWrapper(test1);
	cout << value << endl;

	value = FuncWrapper(test2, 2);
	cout << value << endl;

	string strvalue = FuncWrapper(test3, "abc", "def");
	cout << strvalue << endl;
}

struct Complicated
{
	int year;
	double country;
	string name;
	
	Complicated(int y, double c, string n)
		: year(y), country(c), name(n)
	{ cout << "is constructed" << endl; }

	Complicated(const Complicated &other)
		: year(other.year), country(other.country), name(other.name)
	{ cout << "is moved" << endl; }
};

void TestEmplaceFunc()
{
	map<int, Complicated> mCom;
	int year		= 4;
	double country	= 5.0;
	string name		= "C++";

	cout << "--insert--" << endl;
	mCom.insert(std::make_pair<int, Complicated>(4, Complicated(year, country, name)));
	
	cout << "--emplace--" << endl;
	mCom.emplace(4, Complicated(year, country, name));

	cout << "--emplace back--" << endl;
	vector<Complicated> vecCom;
	vecCom.emplace_back(year, country, name);	
	cout << "--puch back-- " << endl;
	vecCom.push_back(Complicated(year, country, name));	

}

struct Key {
	string first;
	string second;
};

struct KeyHash {
	std::size_t operator()(const Key& k) const
	{
		return std::hash<std::string>()(k.first) ^
				(std::hash<string>()(k.second) << 1);
	}
};

struct KeyEqual {
	bool operator() (const Key& lhs, const Key& rhs) const
	{
		return lhs.first == rhs.first && lhs.first == rhs.second;	
	}
};

void TestUnorderedContainerFunc()
{
	std::unordered_map<string, string> m1;

	std::unordered_map<int, string> m2 =
	{
		{1, "foo"},
		{2, "bar"},
		{3, "baz"}
	};

	// copy constructor
	std::unordered_map<int, string> m3 = m2;

	// move constructor
	std::unordered_map<int, string> m4 = std::move(m2);

	//range constructor
	std::vector<std::pair<std::bitset<8>, int>> v = {{0x12, 1}, {0x01, -1}};

	//construct for a custom type
	std::unordered_map<Key, std::string, KeyHash, KeyEqual> m6 = 
	{
		{{"John", "Doe"}, "example"},
		{{"Mary", "Sue"}, "another"}
	};

}

}
#endif // lvalue_h
