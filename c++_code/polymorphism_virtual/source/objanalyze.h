/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef objanalyze_h
#define objanalyze_h

#include <iostream>

using std::cout;
using std::endl;

#define VIRTUAL_PARENT_A
#define VIRTUAL_PARENT_B

namespace ObjAnalyze
{
class ParentA
{
public:
	ParentA()
	{
		cout << "parent0A address "  << this << endl;
	}

#ifdef VIRTUAL_PARENT_A
	virtual ~ParentA()
	{}
#endif // VIRTUAL_PARENT_A

	void Func0A()
	{
		cout << "parent0A Func0A, address "  << this << endl;
	}

private:
	int m_age;
	int m_high;

};

class ParentB
{
public:
	ParentB()
	{
		cout << "parent0B address "  << this << endl;
	}

#ifdef VIRTUAL_PARENT_B
	virtual ~ParentB()
	{}
#endif //  VIRTUAL_PARENT_B

	void Func0B()
	{
		cout << "parent0B Func0B, address "  << this << endl;
	}

private:
	int m_grade;
	int m_class;

};

class Child : public ParentA, public ParentB
{
public:
	Child()
	{
		cout << "child address "  << this << endl;
	}

	void Func0A()
	{
		cout << "child Func0A "  << this << endl;
	}

};

void test_this_point_address()
{
	cout << "ParentA size " << sizeof(ParentA) << endl;
	cout << "ParentB size " << sizeof(ParentB) << endl;
	cout << "Child size " << sizeof(Child) << endl;

	Child child;
	child.Func0A();
	child.ParentA::Func0A();
	child.Func0B();
	system("pause");

	// 1.parentA,B都没有virtual function
	// ParentA size 8
	// ParentB size 8
	// Child size 16
	// parent0A address 00AFFD78
	// parent0B address 00AFFD80
	// child address 00AFFD78
	// child Func0A 00AFFD78
	// parent0A Func0A, address 00AFFD78
	// parent0B Func0B, address 00AFFD80

	// 2.parentA含有virtual function，B没有
	// ParentA size 12
	// ParentB size 8
	// Child size 20
	// parent0A address 00EFF7B8
	// parent0B address 00EFF7C4
	// child address 00EFF7B8
	// child Func0A 00EFF7B8
	// parent0A Func0A, address 00EFF7B8
	// parent0B Func0B, address 00EFF7C4

	// 3.parentB含有virtual function，A没有
	// ParentA size 8
	// ParentB size 12
	// Child size 20
	// parent0A address 004FF700
	// parent0B address 004FF6F4
	// child address 004FF6F4
	// child Func0A 004FF6F4
	// parent0A Func0A, address 004FF700
	// parent0B Func0B, address 004FF6F4

	// 4.parentA,B都含有virtual function
	// ParentA size 12
	// ParentB size 12
	// Child size 24
	// parent0A address 0077F870
	// parent0B address 0077F87C
	// child address 0077F870
	// child Func0A 0077F870
	// parent0A Func0A, address 0077F870
	// parent0B Func0B, address 0077F87C
	
}

}

#endif // objanalyze_h