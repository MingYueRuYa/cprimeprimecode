/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 桥模式：将抽象部分和实现部分抽离，使得可以相互独立的变化
* 当对象有个两个非常强的变化维度时，考虑将他们分开，各自可以独立的变化。最后在组合起来，就是一个完整的产品
*
*/

#ifndef bridge_h
#define bridge_h

#include <iostream>
#include <string>

using std::cout;
using std::endl;

namespace bridge
{
class OperationSystem
{
public:
    virtual bool InstallOS() { return true; }
};

class LinuxOS : public OperationSystem
{
public:
    bool InstallOS() 
    { 
        cout << "install Linux os..." << endl; 
        return true;
    }
};

class MacOS : public OperationSystem
{
public:
    bool InstallOS() 
    { 
        cout << "install Mac os..." << endl; 
        return true;
    }
};

class WinOS : public OperationSystem
{
public:
    bool InstallOS() { cout << "install Windows os..." << endl; }
};

class Computer
{
public:
    Computer(OperationSystem *pOS) : mOS(pOS) {}

    virtual ~Computer()  //父类中写了虚析构函数，进行了资源的释放
    {
        if (nullptr == mOS) { return; }

        delete mOS;
        mOS = NULL;
    }

    virtual void InstallOS() {}

protected:
    OperationSystem *mOS;
};

class Dell : public Computer
{
public:
    Dell(OperationSystem *pOS) : Computer(pOS) {}

    ~Dell() {}

    void InstallOS() { mOS->InstallOS(); }
};

class HP : public Computer
{
public:
    HP(OperationSystem *pOS) : Computer(pOS) {}

    ~HP() {}

    void InstallOS() { mOS->InstallOS(); }
};

class Intel : public Computer
{
public:
    Intel(OperationSystem *pOS) : Computer(pOS) {}

    ~Intel() {}

    void InstallOS() { mOS->InstallOS(); }
};

    static void test_bridge()
    {
        cout << "######################################\n" \
                "##  this is bridge demo...          ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

        Computer *dellcomputer = new Dell(new LinuxOS());
        dellcomputer->InstallOS();

        Computer *hpcomputer = new Dell(new MacOS());
        hpcomputer->InstallOS();

        delete dellcomputer;
        dellcomputer = NULL;

        delete hpcomputer;
        hpcomputer = NULL;

    }

};

#endif //bridge_h
