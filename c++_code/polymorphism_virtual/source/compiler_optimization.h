/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

/*
	测试编译器的优化问题，从编译器的角度看问题
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
	{ 
        cout << "compiler:" << type_compiler 
             << " level:" << type_level
             << " call ctor" << endl; 
    }

	OptimizationA(const OptimizationA &rhs)
		: type_compiler(rhs.type_compiler+1),
		  type_level(rhs.type_level+1) 
	{ 
        cout << "compiler:" << type_compiler 
             << " level:" << type_level
             << " call copy ctor" << endl; 
    }

	virtual ~OptimizationA()
	{ 
        cout << "compiler:" << type_compiler 
             << " level:" << type_level
             << " call dtor" << endl; 
    }

private:
	int type_compiler;
	int type_level;
};

// 程序员视角
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
