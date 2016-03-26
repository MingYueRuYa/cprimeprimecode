/*
 * std::move 
 * 在使用std::move之后，我们不在使用变量
 * */
#include <iostream>
#include <utility>

using namespace std;

int main(void)
{
	int var1 = 10;
	int &var2 = var1;
	var2 = 20;
	cout << var1 << endl;
	//int &&var3 = 3;
	int &&var3 = std::move(var1);
	cout << var3 << endl;
	cout << "var1 " << var1 << endl;
	//int &var4 = var2 + 20; //error
	//const int var5 = 20; //error
	//int &var4 = var5;
	const int &var4 = 4;
	cout << "var1 " << var1 << endl;
	return 0;
}
