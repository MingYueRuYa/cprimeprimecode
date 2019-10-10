/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

/*
	���Ա��������Ż����⣬�ӱ������ĽǶȿ�����
*/

#ifndef compiler_optimization_h
#define compiler_optimization_h

#include <iostream>

using std::cout;
using std::endl;

namespace compiler_optimization
{
class OptimizationA
{
public:
	OptimizationA(int compiler, int level) 
		: type_compiler(compiler),
		  type_level(level)
	{ cout << "call ctor" << endl; }

	OptimizationA(const OptimizationA &rhs)
		: type_compiler(rhs.type_compiler),
		  type_level(rhs.type_level) 
	{ cout << "copy ctor" << endl; }

	virtual ~OptimizationA()
	{ cout << "call dtor" << endl; }

private:
	int type_compiler;
	int type_level;
};

// ����Ա�ӽ�
OptimizationA ProgramerPerspective()
{
	OptimizationA oa(1, 2);
	return oa;
}

void test_compiler_optimization()
{
	OptimizationA oa = ProgramerPerspective();	
}

}

#endif // compiler_optimization_h