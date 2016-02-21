/*
 * 函数对象: 定义了调用操作符的类，其对象称为函数对象
 * 重载函数调用操作符
 * 一元函数对象
 * 	一元谓词(只有一个参数，且返回值为bool)
 * 二元函数对象
 * 	二元谓词(只有二个参数，且返回值为bool)
 * */
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

struct absInt 
{
	int operator()(int pInt) 
	{
		return pInt < 0 ? -pInt : pInt;
	}
};


/*模板*/
template <typename T>
void PrintElment(const T &pElement)
{
	cout << (pElement < 0 ? -pElement : pElement) << endl;
}

/*类模板*/
template <typename T>
struct DisplayElement 
{
	int mCount;
	
	DisplayElement()
	{
		mCount = 0;
	}

	T operator()(const T &pElement) 
	{
		++mCount;
		return pElement < 0 ? -pElement : pElement;
	}
};

int main01(void)
{
	//absInt absObj;	
	//int tmp = absObj(-42);
	DisplayElement<int> displayelment;
	int tmp = displayelment(-42); 
	cout << tmp << endl;
	//PrintElment(-42);
	vector<int> intvector{1, 2, 3, 4, 5, 6};
	DisplayElement<int> displayelement;
	displayelement = for_each(intvector.begin(), intvector.end(), displayelement);
	cout << displayelement.mCount << endl;
	return 0;
}

template <typename TType>
struct IsMultiple
{
	TType mDivisor;

	IsMultiple(const TType &pDivisor)
	{
		mDivisor = pDivisor;
	}

	//一元谓词
	bool operator()(const TType &pElement)
	{
		return (pElement % mDivisor) == 0;
	}

};

int main02(void)
{
	vector<int> intvector;
	for (int i = 25; i < 100; ++i) {
		intvector.push_back(i);
	}
	
	IsMultiple<int> multiple(3);
	vector<int>::iterator ires;
	ires = find_if(intvector.begin(), intvector.end(), multiple);
	if (ires != intvector.end()) {
		cout << *ires << endl;
	}

	return 0;
}

template <typename TType>
struct Multiple
{
	TType operator() (const TType &pElement1, const TType &pElement2) 
	{
		return pElement1 * pElement2;
	}
};

int main03(void)
{
	vector<int> vector1{1, 2, 3, 4, 5};
	vector<int> vector2{5, 4, 3, 2, 1};
	
	vector<int> vector3;
	vector3.resize(5);
	
	transform(vector1.begin(), vector1.end(), vector2.begin(), vector3.begin(), Multiple<int>());

	for (size_t i = 0; i < vector3.size(); ++i) {
		cout << vector3[i] << " ";
	}
	cout << endl;
	return 0;
}

int to_lower(const int &pChar)
{
	if (! islower(pChar)) {
		return pChar + 32;
	}	
	return pChar;
}

class CompareStringNoCase
{
public:
	bool operator() (const string &pString01, const string &pString02)
	{
		string strlower1;
		strlower1.resize(pString01.size());
		transform(pString01.begin(), pString01.end(), strlower1.begin(), to_lower);

		string strlower2;
		strlower2.resize(pString02.size());
		transform(pString02.begin(), pString02.end(), strlower2.begin(), to_lower);

		return strlower1 < strlower2;
	}
};

int main(void)
{
	set<string, CompareStringNoCase> names;
	names.insert("tom");
	names.insert("liu");
	names.insert("Linux");

	set<string, CompareStringNoCase>::iterator ifind = names.find("Liu");
	if (ifind != names.end()) {
		cout << *ifind << endl;
	}
	return 0;
}
