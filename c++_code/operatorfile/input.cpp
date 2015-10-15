/*
 * 输入
 * */

#include <iostream>
#include <stdlib.h>

using namespace std;

int main01()
{
	char ch;
	cin >> ch;
	cout << (char)(ch - 32);
	cin.get();
	cin.get();
	return 0;
}

int main02()
{
	char ch = 0;
	while ((ch = cin.get()) != '\t') {
		cin.get();	
		cout.put(ch);
	}
	return 0;
}


int main()
{
	char str[10] = {0};
	cin.getline(str, 10);
	cout << str;
	return 0;
}
