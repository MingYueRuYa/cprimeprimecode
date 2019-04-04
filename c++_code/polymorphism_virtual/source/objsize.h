/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef objsize_h
#define objsize_h

#include <iostream>

using std::cout;
using std::endl;

class EmptyClass
{
};

class EmptyClassWithFun
{
public:
	void Fun() {}
};

class EmptyClassWithVirFun
{
public:
	virtual void VirFun() {}
};

void test_obj_size()
{
	cout << "empty class "<< sizeof(EmptyClass) << endl;

	cout << "empty class with function " << sizeof(EmptyClassWithFun) << endl;

	cout << "empty class with virtual function " << sizeof(EmptyClassWithVirFun) << endl;

	//empty class 1
	//empty class with function 1
	//empty class with virtual function 4
}

#endif // objsize_h