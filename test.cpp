#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Foo
{
public:
	Foo()
	{
		cout << "Foo construct..." << endl;
	}

	~Foo()
	{
		cout << "Foo destruct..." << endl;
	}

private:
	int _id;
	long _data;
	string _str;
};

class Demo
{
private:
	int id;
	int age;
	Demo *next;
};

class Demo2
{
public:
	typedef struct demo
	{
		int id;
		int age;
	} demo;

	union {
		demo demo1;
	 	Demo2 *next;
	};

	void setid(const int &pid)
	{
		demo1.id = pid;
	}

	int getid()
	{
		return demo1.id;
	}

	void setage(const int &page)
	{
		demo1.age = page;
	}

	int getage()
	{
		return demo1.age;
	}
};

int main03()
{
	cout << "Demo size: " << sizeof(Demo) << endl;
	cout << "Demo2 size: " << sizeof(Demo2) << endl;

	Demo2 demo2;
	demo2.demo1.id = 1;
	demo2.demo1.age = 1;
	cout << "demo2.demo1.id: " << demo2.demo1.id << endl;
	cout << "demo2.demo1.age: " << demo2.demo1.age << endl;

	demo2.next = new Demo2();
	demo2.next->setid(2);
	demo2.next->setage(3);
	cout << "给next指针赋值：" << endl;
	cout << "demo2.demo1.id: " << demo2.demo1.id << endl;
	cout << "demo2.demo1.age: " << demo2.demo1.age << endl;
	cout << "demo2.next->id: " << demo2.next->getid() << endl;
	cout << "demo2.next->age: " << demo2.next->getage() << endl;

	demo2.demo1.id = 1;
	demo2.demo1.age = 1;
	cout << "给demo1变量赋值：" << endl;
	cout << "demo2.demo1.id: " << demo2.demo1.id << endl;
	cout << "demo2.demo1.age: " << demo2.demo1.age << endl;

	cout << "demo2.next->id: " << demo2.next->getid() << endl;
	cout << "demo2.next->age: " << demo2.next->getage() << endl;

	//result:
		//size: 12
		//Demo2 size: 8
		//demo2.demo1.id: 1
		//demo2.demo1.age: 1
		//给next指针赋值：
		//demo2.demo1.id: 25923592
		//demo2.demo1.age: 1
		//demo2.next->id: 2
		//demo2.next->age: 3
		//给demo1变量赋值：
		//demo2.demo1.id: 1
		//demo2.demo1.age: 1
		//Segmentation fault
  return  0;
}

void *operator new(size_t size)
{
	cout << "global operator new..." << endl;
	return malloc(size);
}

void operator delete(void *start)
{
	cout << "global operator delete..." << endl;
	free(start);
}

int main()
{
	Foo *foo = new Foo();
	delete foo;
	foo = NULL;

	Demo2 *demo = new Demo2();
	delete demo;
	demo = NULL;
	return 0;
}

int main02()
{

	cout << "Foo size: " << sizeof(Foo) << endl;
	cout << "long size: " << sizeof(long)  << endl;
	cout << "string size: " << sizeof(string)  << endl;
	//result:
		//Foo size: 12
		//long size: 4
		//string size: 4
	return 0;
}

int main01()
{
	int a = 0["abc" + 53];
	printf("a = %d\n", a);
	printf("  %d\n", "abc" + 53);
	for (int i = 53; i < 63; i++) {
		printf("%d ", *("abc" + i));
	}
	int a1 = 3["abc" + 53];
	printf("a = %d\n", a1);

//result:
	/*
	a = 0
	  68145
	255 255 127 160 254 255 127 1 0 0 a = 0
	*/
}
