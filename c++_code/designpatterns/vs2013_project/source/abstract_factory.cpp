/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
 * 抽象工厂模式：定义了创建一系列相关和相互依赖对象的接口
 * 
 *
 */

#ifndef abstract_factory_h
#define abstract_factory_h

#include <iostream>

using std::cout;
using std::endl;

namespace abstract_factory 
{
    
#define DELETE_POINT(object) if (nullptr != object) { delete object; object = nullptr; }

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

class MultiCore
{
public:
    virtual void Show() = 0;
};

class MultiCoreA : public MultiCore
{
public:
    void Show()
    {
        cout << "this is multicoreA..." << endl;
    }
};

class MultiCoreB : public MultiCore
{
public:
    void Show()
    {
        cout << "this is multicoreB..." << endl;
    }
};

class Factory
{
public:    
    virtual SingleCore *CreateSingleCore() = 0;
    virtual MultiCore *CreateMultiCore() = 0;
};

class FactoryA : public Factory
{
public:
    SingleCore *CreateSingleCore() { return new SingleCoreA(); }
    MultiCore  *CreateMultiCore() { return new MultiCoreA(); }
};

class FactoryB : public Factory
{
public:
    SingleCore *CreateSingleCore() { return new SingleCoreB(); }
    MultiCore  *CreateMultiCore() { return new MultiCoreB(); }
};

static void test_abstract_factory()
{
    cout << "######################################\n" \
            "## this is abstract factory demo... ##\n" \
            "##                                  ##\n" \
            "######################################"   \
            << endl;
    
    FactoryA *Afactory = new FactoryA();
    SingleCore *basecore1 = Afactory->CreateSingleCore();
    basecore1->Show();

    MultiCore *multicore1 = Afactory->CreateMultiCore();
    multicore1->Show();

    FactoryB *Bfactory = new FactoryB();
    SingleCore *basecore2 = Bfactory->CreateSingleCore();
    basecore2->Show();

    MultiCore *multicore2 = Bfactory->CreateMultiCore();
    multicore2->Show();

    DELETE_POINT(Afactory);
    DELETE_POINT(basecore1);
    DELETE_POINT(Bfactory);
    DELETE_POINT(basecore2);
}

};

#endif //abstract_factory_h
