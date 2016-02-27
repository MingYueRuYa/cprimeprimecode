/*
 * lower_bound 找到第一个匹配的位置
 * upper_bound 找到最后一个匹配的下一个位置
 * 主要应用场景就是插入一个数据不能破坏原来的结构的顺序
 * equal_bound 得到上面的两个表示范围
 * 关联式容器有自己的成员函数 set<int>
 * */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main_lower_bound(void)
{
	int intarray[] = {1, 2, 3, 4, 5, 20};
	vector<int> intvector(intarray, intarray + 8);
	vector<int>::iterator ifind = lower_bound(intvector.begin(), intvector.end(), 5);
	if (ifind != intvector.end()) {
		cout << "index " << ifind - intvector.begin() + 1 << endl;
	}
	return 0;
}

int main_upper_bound(void)
{
	int intarray[] = {1, 2, 3, 4, 5, 5, 5, 20};
	vector<int> intvector(intarray, intarray + 8);
	vector<int>::iterator ifind = upper_bound(intvector.begin(), intvector.end(), 5);
	if (ifind != intvector.end()) {
		cout << "index " << ifind - intvector.begin() + 1 << endl;
	}

	return 0;
}

bool Greater(const int &pMaxValue, const int &pMinValue)
{
	return pMaxValue < pMinValue;
}

int main(void)
{
	int intarray[] = {1, 2, 5, 4, 5, 5, 3, 20};
	vector<int> intvector(intarray, intarray + 8);
	sort(intvector.begin(), intvector.end(), Greater);
	pair<vector<int>::iterator, vector<int>::iterator> equalpair;
	equalpair = equal_range(intvector.begin(), intvector.end(), 5, Greater);
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});	
	cout << endl;
	cout << "index "<<  equalpair.first - intvector.begin() << endl;
	cout << "index "<<  equalpair.second - intvector.begin() << endl;
	return 0;
}
