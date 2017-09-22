/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 责任链模式：每个对象都有处理的机会,从而避免发送者和接受者之间的耦合关系.将
*	对象连成一条链，将请求沿着这条链传递
*/

#ifndef chain_of_responsibility_h
#define chain_of_responsibility_h

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

namespace chain_of_responsibility
{

class Manager
{
public:
	Manager(Manager *pManager, const string &pName) : mManager(pManager), mName(pName) {}

	virtual ~Manager() = default;

    virtual void AddMoney(const string pName, const int pMoney) {}

protected:
    Manager *mManager;

    string mName;

};

class CommonManager : public Manager
{
public:
	CommonManager(Manager *pManager, const string &pName) : Manager(pManager, pName) {}

    virtual ~CommonManager() {}

    void AddMoney(const string pName, const int pMoney)
    {
        if (pMoney < 500) {
            cout << "common manager " << mName << " support " << pName << " " << pMoney << endl;
        } else {
            cout << "common manager " << mName << " no permission to handle" << endl;
            mManager->AddMoney(pName, pMoney);
        }
    }
};

class Director : public Manager
{
public:
	Director(Manager *pManager, const string &pName) : Manager(pManager, pName) {}

    virtual ~Director() {}

    void AddMoney(const string pName, const int pMoney)
    {
        if (pMoney < 3000) {
            cout << "director " << mName << " support " << pName << " " << pMoney << endl;
        } else {
            cout << "director " << mName << " no permission to handle" << endl;
            mManager->AddMoney(pName, pMoney);
        }
    }
};

class GeneralManager : public Manager
{
public:
	GeneralManager(Manager *pManager, const string &pName) : Manager(pManager, pName) {}

    virtual ~GeneralManager() {}

    void AddMoney(const string pName, const int pMoney)
    {
        cout << "GeneralManager " << mName << " support " << pName << " " << pMoney << endl;
    }
};

    static void test_chain_of_responsibility()
    {
        cout << "######################################\n" \
                "## this is chain of responsibility  ##\n" \
                "## demo...                          ##\n" \
                "######################################"   \
             << endl;

        GeneralManager *generalmanager = new GeneralManager(NULL, "general manager");
        Director *director = new Director(generalmanager, "director");
        CommonManager *common = new CommonManager(director, "A");
        common->AddMoney("D", 5000);
        common->AddMoney("E", 500);
        common->AddMoney("F", 2500);
        delete common, director, generalmanager;
        common   = nullptr;
        director = nullptr;
        generalmanager = nullptr;
    }

};

#endif //chain_of_responsibility_h
