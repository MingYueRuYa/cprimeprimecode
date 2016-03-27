/*
 * std::move 
 * 在使用std::move之后，我们不在使用变量
 * */
#include <iostream>
#include <utility>

using namespace std;

int main01(void)
{
	int var1 = 10;
	int &var2 = var1;
	var2 = 20;
	cout << var1 << endl;
	//int &&var3 = 3;
	int &&var3 = std::move(var1);
	cout << "var3 " << &var3 << " var1 " << &var1; //var3 address is equial var1
//	cout << var3 << endl;
//	cout << "var1 " << var1 << endl;
	//int &var4 = var2 + 20; //error
	//const int var5 = 20; //error
	//int &var4 = var5;
	const int &var4 = 4;
	//cout << "var1 " << var1 << endl;
	int *i1 = new int(10);
	int *&& i2 = NULL;
	i2 = std::move(i1);
	delete i1;
	i1 = 0x0000000;
	cout << " i2 " << *i2 << endl;
	return 0;
}

typedef struct __Teacher
{
	char *name;
	int age;
}Teacher;

int main(void)
{
	Teacher *teacher = new Teacher();
	teacher->name = "linux";
	teacher->age = 30;
	Teacher *&&t1 = std::move(teacher);
	delete teacher;
	printf("%0x, %0x", teacher, t1);
	cout << t1->name << "  " << t1->age << endl;
	return 0;
}




