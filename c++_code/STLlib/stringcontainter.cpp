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

int main(void)
{
	string tmpstring("hello string");	
	for (string::size_type index = 0; index < tmpstring.length(); ++index) {
		cout << tmpstring[index] << " ";
	}
	cout << endl;
	return 0;
}
