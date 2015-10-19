/*
 * 文本文件的提取
 * */
#include <iostream>
#include <stdlib.h>


using namespace std;

int main01(int argc, char **argv)
{
	char buf[80];
	//提取一段文本，最大长度为80，遇到#结束
	//超过80，只要80个字符
	//默认是以'\n'为结束符号
	cin.get(buf, 80, '#');
	cout << buf << "\n";
	return 0;
}

int main(int argc, char **argv)
{
	char buff[8];	
	//逐行读取，可以反复读取
	cin.getline(buff, 8, ',');
	cout << buff << "\n";
	cin.getline(buff, 8, ',');
	cout << buff << "\n";
	return 0;
}

