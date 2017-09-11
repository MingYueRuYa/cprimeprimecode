/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com (http://www.2144.cn)
** All rights reserved.
**
****************************************************************************/

#include <iostream>

using std::cout;
using std::endl;

#include "simple_factory.cpp"
#include "factory.cpp"
#include "abstract_factory.cpp"

int main(int argc, char *argv[])
{
    simplefactory::test_simple_factory();
    cout << "----------------------------------------------" << endl;

    factory::test_factory();
    cout << "----------------------------------------------" << endl;

    abstractfactory::test_abstract_factory();
    cout << "----------------------------------------------" << endl;

    system("pause");
    return 0;
}