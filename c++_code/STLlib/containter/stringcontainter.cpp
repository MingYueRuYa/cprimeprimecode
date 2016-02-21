/*
 * copy
 * iterate
 * asign
 * add
 * delete
 * modify
 * serach
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int main01()
{
	//init string
	string strname = "I am a student";	
	string strname02("I am a student");

	string str03 = strname + strname02;
	
	str03.append(" this is fine.");
	str03 += " operate +=.";

	str03.insert(str03.begin(), 'X');
	str03.insert(str03.begin() + 3,3, 'X');
	//从第三个字符开始，删除4个字符
	//str03.erase(3, 4);	
	str03.replace(1, 4, "AAAA");
	cout << str03 <<endl;


	string strdump = "linux unix freeBSD window linux linux";
	int pos = strdump.find("linux", 0);
	while (pos >= 0) {
		cout << pos << endl;
		pos = strdump.find("linux", pos + 5);
	}

	return 0;
}

int main02(void)
{
	string tmpstring("hello string");	
	for (string::size_type index = 0; index < tmpstring.length(); ++index) {
		cout << tmpstring[index] << " ";
	}
	cout << endl;
	string findstring("linux windows");
	string::size_type pos = findstring.find("linux2");
	if (string::npos == pos) {
		cout << "Not find substring." << endl;
	} else {
		cout << pos << endl;
	}
	string::iterator positerator = find(findstring.begin(), findstring.end(), 'l');
	if (positerator != findstring.end()) {
		cout << *positerator << endl;
	}
	return 0;
}

//c string 与 c++ string 相互转换
int main03(void)
{
	const char *cstring = "cstring";
	string strstr(cstring);
	cout << strstr << endl;
	cout << strstr.c_str() << endl;
	return 0;
}

//字符串 增加
int main04(void)
{
	string addstring("hello");
	addstring += " world";
	cout << addstring << endl;
	addstring.insert(5, " linux");
	cout << addstring << endl;
	addstring.append(" unix");
	cout << addstring << endl;
	return 0;
}

int main05(void)
{
	string daystring = "today is good day!";	
	string::size_type pos = daystring.find("day");
	while (string::npos != pos) {
		cout << "find pos is " << pos << endl;
		++pos;
		pos = daystring.find("day", pos);
	}
	return 0;
}

//删除string
int main06(void)
{
	string hellostring = "hellostring linux world";
	hellostring.erase(10, 5);
	cout << hellostring << endl;
	string::iterator deliterator = find(hellostring.begin(), hellostring.end(), 'l');
	while (deliterator != hellostring.end()) {
		hellostring.erase(deliterator);
		deliterator = find(hellostring.begin(), hellostring.end(), 'l');

	}
	cout << hellostring << endl;
	return 0;
}

int to_upper(int c)
{
	if (islower(c)) {
		return (c - 32);
	}
	return c;
}

//关于string 算法
int main(void)
{
	string reversestring = "reversestring";
	reverse(reversestring.begin(), reversestring.end());
	//cout << reversestring << endl;

	string strinput("");
	string output("");
	getline(cin, strinput);	
	transform(strinput.begin(), strinput.end(), strinput.begin(), to_upper);
	cout << strinput << endl;
	return 0;
}
