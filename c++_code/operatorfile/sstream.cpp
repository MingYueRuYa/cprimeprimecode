/*
 *sstream class operate
 */

#include <iostream>
#include <sstream>
#include <strstream>
#include <string>
#include <string.h>

using namespace std;

int main01()
{
  	//字符串进行输入
  	stringstream mystr;
	//连个字符输入
	mystr.put('X').put('Y');
	//字符串输入
	mystr << "ZXCV";
	std::cout << mystr.str() << "\n";

	char ch;
	mystr >> ch;
	cout << "\n";
	cout.put(ch).put('\n');
	std::cout << mystr.str() << "\n";
	return 0;
}


int main02()
{
  	//sprintf功能
	stringstream mystr;
	char cmd1[20] = {0};
	char cmd2[20] = {0};
	//读取
	cin.getline(cmd1, 30).getline(cmd2, 30);
	//字符打印
	mystr << cmd1 << "&" << cmd2;
	//接受字符串
	string str = mystr.str();
	cout << str << endl;

	system(str.c_str());
	char cstr[50] = {0};
	strcpy(cstr, str.c_str());
	cout << cstr << endl;
	for (char *p = cstr; *p != '\0'; p++) {
		if (*p == '&') {
		  	*p = ' ';	
		}	
	}
	char newcmd1[20] = {0};
	char newcmd2[20] = {0};
	stringstream newstr(cstr);
	newstr >> newcmd1 >> newcmd2;
	cout << newcmd1 << "---" << newcmd2 << endl;
  	return 0;
}

struct MyStruct
{
	string str1, str2, str3;
	double db;
	int num;
	char ch;
};

int main03()
{
	string mystring("china google microsoft 12.9 123 A");  	
	MyStruct struct1;
	//扫描一个字符串扫描流, 能够根据空格分割字符串
	istringstream input(mystring);
	input >> struct1.str1 >> struct1.str2 >> struct1.str3 >> struct1.db >> struct1.num >> struct1.ch;
	cout << struct1.str1 << "--" << struct1.str2 << "--" << struct1.str3 << "--" << struct1.db << "--" << struct1.num << "--" << struct1.ch;
  	return 0;
}

int main04()
{
  	char mystring[50] = "china#123#A";
	for (char *p = mystring; *p != '\0'; p++) {
	  	if (*p == '#') {
		  	*p = ' ';	
		}	
	}
	string str1;
	int num;
	char ch;
	istringstream isstream(mystring);
	isstream >> str1 >> num >> ch;
	cout << str1 << "--" << num << "--" << ch << "\n";
	return 0;  	
}

int main05()
{
  	char str[100] = {0};
	ostrstream myout;
	char str1[50] = {"a1234567bo"};
	myout << "a123b" << 123 << 234.89 << 'h' << str1 << endl;
	cout << myout.str() << "\n";
	return 0;
}

int main()
{
  /*
	char str[100] = {0};
	ostringstream myout(str, sizeof(str));
	char str1[50] = "1234567";
	myout << "linux" << str1 << ends;
	cout << myout.str() << endl;
	cout << str << endl;
  */	
 	return 0;
}

	
	
	
	

