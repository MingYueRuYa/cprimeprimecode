/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com (http://www.2144.cn)
** All rights reserved.
**
****************************************************************************/

/*
 * 简单工厂模式：在工厂类中做判断，从而创造对应的产品。当前增加新的产品时，就需要修改工厂类
 * 缺点：当前增加新的产品时，就需要修改工厂类。违反了开放封闭原色
 *
 */

#ifndef simple_factory_h
#define simple_factory_h

#include <iostream>

using std::cout;
using std::endl;

namespace simple_factory 
{
typedef enum _CoreType
{
    CoreA,
    CoreB
} CoreType;

class SingleCore
{
public:
    virtual void Show() = 0;
};

class SingleCoreA :public SingleCore
{
public:
    void Show()
    {
        cout << "this is singleCoreA..." << endl;
    }
};

class SingleCoreB : public SingleCore
{
public:
    void Show()
    {
        cout << "this is singleCoreB..." << endl;
    }
};

class Factory
{
public:    
    static SingleCore *CreateSingleCore(const CoreType pCoreType)
    {
        if (pCoreType == CoreA) {
            return new SingleCoreA();
        } else if (pCoreType == CoreB) {
            return new SingleCoreB();
        } else {
            return NULL;
        }
    }
};

static void test_simple_factory()
{
    cout << "######################################\n" \
            "##  this is simple factory demo...  ##\n" \
            "##                                  ##\n" \
            "######################################"   \
            << endl;
    SingleCore *basecore1 = Factory::CreateSingleCore(CoreA);
    basecore1->Show();
    SingleCore *basecore2 = Factory::CreateSingleCore(CoreB);
    basecore2->Show();
}
};

#endif //simple_factory_h
