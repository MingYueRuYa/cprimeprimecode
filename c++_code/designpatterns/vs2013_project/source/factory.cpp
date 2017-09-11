/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com (http://www.2144.cn)
** All rights reserved.
**
****************************************************************************/

/*
 * 工厂模式：是指定义一个用于创建对象的接口，让子类决定实例化哪一个类，
 * 缺点：解决简单工厂方法违反了开发封闭原则，但是也来一个缺点就是，如果新的产品就要增加一个工厂需要定义更多的类
 *
 */

#ifndef factory_h
#define factory_h

#include <iostream>

using std::cout;
using std::endl;

namespace factory 
{
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
    virtual SingleCore *CreateSingleCore() = 0;
};

class FactoryA : public Factory
{
public:
    SingleCore *CreateSingleCore() { return new SingleCoreA(); }
};

class FactoryB : public Factory
{
public:
    SingleCore *CreateSingleCore() { return new SingleCoreB(); }
};

static void test_factory()
{
    cout << "######################################\n" \
            "##  this is factory demo...         ##\n" \
            "##                                  ##\n" \
            "######################################"   \
            << endl;
    
    SingleCore *basecore1 = (new FactoryA())->CreateSingleCore();
    basecore1->Show();
    SingleCore *basecore2 = (new FactoryB())->CreateSingleCore();
    basecore2->Show();
}

};

#endif //factory_h
