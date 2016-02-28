/*
 * copy()
 * copy_backward()
 * 注意:
 * 	1.没有copy_if()算法,可以使用remove_copy_if()算法
 * 	2.复制过程中要逆转元素次序,使用reverse_copy()算法
 * 	3.把容器內所有元素赋值给另个一个容器,要使用赋值操作符或容器的assign()成员函数
 * 	4.复制过程中删除某些元素,使用remove_copy()和remove_copy_if()算法
 * 	5.复制中改变元素,使用transform()或replace_copy()算法
 *
 * 	copy, copy_backward的时候注意
 * 	1.copy的目的地大小是否可以容纳被copy对象
 * 	2.还可以copy到输入流中
 * 	3.在copy的时候不能修改copy的元素
 * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

int main01(void)
{
	vector<int> intvector{1, 2, 3, 4, 6, 7, 8, 9};

	list<int> intlist;
	//在插入的时候用了back_inserter函数适配器,确保intlist有足够的容量
	//copy(intvector.begin(), intvector.end(), back_inserter(intlist));
	//for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	//cout << endl;
	//反序插入，这样插入的效率没有reverser_copy
	//copy(intvector.rbegin(), intvector.rend(), back_inserter(intlist));
	//for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	//cout << endl;
	//这样的逆序插入方法效率更高
	//reverse_copy(intvector.begin(), intvector.end(), back_inserter(intlist));
	//for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	//copy 到输入流中
	
	ostream_iterator<int> out_it (std::cout,", ");
	copy(intvector.begin(), intvector.end(), out_it);
	cout << endl;
	return 0;
}

int main02(void)
{
	vector<int> intvector{1, 2, 3, 4, 6, 7, 8, 9};
	
	list<int> intlist(intvector.size(), 0);
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	copy_backward(intvector.begin(), intvector.end(), intlist.end());
	for_each(intlist.begin(), intlist.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	return 0;
}

int main03(void)
{
	vector<int> intvector{1, 2, 3, 4, 6, 7, 8, 9};
	intvector.insert(intvector.end(), 10, 0);	
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	copy(intvector.begin() + 10, intvector.begin() + 16, intvector.begin());
	for_each(intvector.begin(), intvector.end(), [](const int &pValue){ cout << pValue << " ";});
	cout << endl;
	return 0;
}


