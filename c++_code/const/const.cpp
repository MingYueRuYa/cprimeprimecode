#include <iostream>

using std::cout;
using std::endl;


/*
 * redefinition synatx error
int add(int num)
{
	cout << num + 1 << endl;
}

int add(const int num)
{
	cout << num + 2 << endl;
}
*/
int add(const int &num)
{
	cout << num + 1 << endl;
}

int add(int &num)
{
	cout << num + 2 << endl;
}

int main()
{
	int number = 0;
	const	int &num = number;
	int &num02 = number;
	add(num02);	
	return 0;
}
