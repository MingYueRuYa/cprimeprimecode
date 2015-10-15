/*
 *sstream class operate
 */

#include <iostream>
#include <sstream>
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


int main()
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






