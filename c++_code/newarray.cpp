/**
 *  new type array
 */
#include <iostream>
#include <array>
#include <string>
#include <stdlib.h>
#include <vector> //c++的标准库

using std::vector;
using std::array;
using std::string;

int main()
{
	vector<string> str01; 
	str01.push_back("notepadqq");
	str01.push_back("firefox");
	str01.push_back("git");	

	//反向迭代器
	vector<string>::reverse_iterator rbegin = str01.rbegin();
	vector<string>::reverse_iterator rend = str01.rend();
	//注意：rend不是指向最后一个数据，而是指向结尾的下一个结点
A:	if (rbegin != rend) {
		std::cout << *--rend << "";
		goto A;
	}

	return 0;
}
int main06()
{
	vector<string> str01; 
	str01.push_back("notepadqq");
	str01.push_back("firefox");
	str01.push_back("git");
	vector<string>::iterator ibegin, iend; //迭代器
	ibegin = str01.begin(); //data start
	iend = str01.end(); //data end
	//正向迭代
	//for(; ibegin != iend; ibegin++) {
	//	std::cout << *ibegin << " "; //获取指针指向的数据
	//}
	//反响迭代
	while(iend != ibegin) {
		std::cout << *--iend << " "; 	
	}
	return 0;
}

int main05()
{
	vector<string> str01; //动态字符串数组
	//可以反复利用
	str01.push_back("notepadqq");
	str01.push_back("firefox");
	str01.push_back("git");
	str01.pop_back(); //删除最后一个
	for(int i = 0; i < str01.size(); i++) {
		std::cout << str01[i] << " ";
	}
	return 0;
}


int main04()
{
	array<int, 5> myint1 = {1, 2, 3, 4, 5};
	array<int, 5> myint2 = {6, 7, 8, 9, 10 };
	array<int, 5> myint3 = {11, 12, 13, 14, 15};
	//第一种方式初始化
	//array<array<int,5>,3> myint = {myint1, myint2,myint3};
	//第二种方式初始化
	array<array<int, 5>, 3> myint = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
	, 12, 13, 14, 15};
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 5; j++) {
			std::cout<< myint[i][j] << " ";
		}
		std::cout << "\n";
	}
	return 0;	
}




int main03()
{
	std::string str01 = "fire";
	std::string str02 = "fox";
	system((str01 + str02).c_str());
	return 0;
}
int main02()
{
	std::array<std::string, 3> str01 = {"notepadqq", "chrome", "firefox"};
	for(int i = 0; i < 3; i++) {
		std::cout << str01[i] << std::endl;
		system(str01[i].c_str());
	}
	return 0;
}
int main01()
{
	double db[4] = { 1.1, 2.2, 3.3, 4.4};
	std::array<double, 4> dbnew1 = { 10.1, 10.2, 10.3, 10.4};
	//实现数组之间整体的操作
	std::array<double, 4> dbnew2 = dbnew1; 
	for(int i = 0; i < 4; i++) {
		std::cout << dbnew2[i]	<< "  " << dbnew1[i] <<std::endl;
	}
	return 0;
}
