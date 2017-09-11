/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com (http://www.2144.cn)
** All rights reserved.
**
****************************************************************************/

#include <iostream>

#include "designpatternpack.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    simplefactory::test_simple_factory();
    cout << "----------------------------------------------" << endl;

    factory::test_factory();
    cout << "----------------------------------------------" << endl;

    abstractfactory::test_abstract_factory();
    cout << "----------------------------------------------" << endl;

    strategy::test_strategy();
    cout << "----------------------------------------------" << endl;

    system("pause");
    return 0;
}