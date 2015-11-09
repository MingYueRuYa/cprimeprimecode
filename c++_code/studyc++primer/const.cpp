#include <iostream>
#include <string>
using std::cout;
using std::cin;

typedef char * mystring;


int main()
{
	char charray[13] = {"hello linux"};
	char charray02[13] = {"hello linux"};
	//str本身是常量的，不是指向的对象是常量
	const mystring str = charray;	
	*str = 'A';
	//str = charray02;	
	mystring pstr = "hello world";
	mystring pstr01 = "xllo nihao";
	//*strstr是const常量， strstr不是常量
	const mystring *strstr = &pstr; 
	strstr = &pstr01;	
	printf("%s\n", *strstr);
	

	char **ppch = NULL;
	char *pch = NULL;
	char a = 'a';
	char b = 'b';
	pch = &a;
	ppch = &pch;
	*ppch = &b;
	printf("%c,%c\n", **ppch, *pch);
	return 0;
}
