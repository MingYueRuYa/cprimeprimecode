/*
 * 1.遍历数据
 * 2.利用函数指针和函数对象修改数据
 * 3.返回值为传进去的函数对象
 * */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Print(int &pValue)
{
	pValue += 1;
	cout << pValue << " "; 
}

class AddValue
{
public:
	AddValue(int pAddValue): mAddValue(pAddValue)
	{}

	void operator() (int &pValue)
	{
		pValue += mAddValue;
		cout << pValue << " "; 
	}

private:
	int mAddValue;

};

template <class T>
class MeanValue
{
public:
	MeanValue()
	{}

	void operator() (T &pValue)
	{
		++mNum;
		mSum += pValue;
	}

	operator double ()
	{
		return static_cast<double>(mSum) / static_cast<int>(mNum);
	}

private:
	long mNum = 0;
	long mSum = 0;

};

int main(void)
{
	vector<int> intvector;
	for (int i = 0; i < 10; ++i) {
		intvector.push_back(i);	
	}
	
	//1.函数指针的形式不能修改vector中的数据
	for_each(intvector.begin(), intvector.end(), Print);
	cout << endl;

	//2.函数对象可以修改
	for_each(intvector.begin(), intvector.end(), AddValue(2));
	cout << endl;

	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;

	//3.for_each返回值 返回的对象为传递进去的函数对象
	//MeanValue<int> meanvalue = for_each(intvector.begin(), intvector.end(), MeanValue<int>());
	//cout << meanvalue.mNum << " " << meanvalue.mSum;
	//重载了double声明符
	double meanvalue = for_each(intvector.begin(), intvector.end(), MeanValue<int>());
	cout << meanvalue << endl;
	cout << endl;

	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	
	return 0;
}
