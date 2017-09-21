/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 中介模式：用一个中介对象封装一系列的对象交互。使得各个对象不需要显式地相互引用。从而使其松耦合。
* 	从而可以独立的改变他们之间的变化
*   1.一组对象以定义良好但是复杂的方式进行通信。产生的相互依赖关系结构混乱且难以理解；
*   2.一个对象引用其他很多对象并且直接与这些对象通信，导致难以复用该对象；
*   3.想定制一个分布在多个类中的行为，而又不想生成太多的子类。
*   外观模式与中介者模式的不同之处在于它是对一个对象子系统进行抽象，从而提供了一个更为方便的接口
*   外观模式的协议是单向的，即外观模式向子系统提出请求，但反过来则不行；而对于中介者模式，是进行多个对象之间的协作，通信是多向的
*/

#ifndef mediator_h
#define mediator_h

#include <iostream>
#include <string>
#include <list>
#include <map>

using std::map;
using std::pair;
using std::list;
using std::cout;
using std::endl;
using std::string;

namespace mediator
{

class Mediator;

class Colleague
{
public:
    Colleague() = default;
    virtual ~Colleague() = default;

    virtual void SendMessage(const string &pMessage) {}

    virtual void ReceiveMessage(const string &pMessage) {}

    void SetMediator(Mediator *pMediator) 
    {
        if (nullptr == pMediator) { return; }
        mMediator = pMediator;
    }

protected:
    Mediator *mMediator;

};

class Mediator
{
public:
    Mediator() = default;
    virtual ~Mediator() {}

    virtual void SendMessage(const string &pMessage, Colleague *pColleague) = 0;
};

class ConcreteMediator : public Mediator
{
public:
    ConcreteMediator() = default;
    virtual ~ConcreteMediator() 
    { 
        map<Colleague *, list<Colleague *> *>::iterator ibegin = mColleagueMap.begin();
        while (ibegin != mColleagueMap.end()) {
            delete ibegin->second;
            ibegin->second = NULL;
            ++ibegin;
        }
        mColleagueMap.clear();
        cout << "concrete mediator dtor." << endl; 
    }

public:
    void SendMessage(const string &pMessage, Colleague *pColleague)
    {
        list<Colleague *> *colleaguelist = mColleagueMap[pColleague];
        if (nullptr == colleaguelist) { return; }

        for (Colleague *colleague : (*colleaguelist)) {
            colleague->ReceiveMessage(pMessage);
        }
    }

    void AddColleague(Colleague *pColleague1, Colleague *pColleague2)
    {
        list<Colleague *> *colleaguelist = mColleagueMap[pColleague1];
        if (nullptr == colleaguelist) { 
            colleaguelist = new list<Colleague *>(); 
            mColleagueMap[pColleague1] = colleaguelist;
        } 
        colleaguelist->push_back(pColleague2);
    }

private:
    map<Colleague *, list<Colleague *> *> mColleagueMap;
};


class ColleagueA : public Colleague
{
public:
    ColleagueA() = default;

    ~ColleagueA() { cout << "colleagueA dtor." << endl; }

    void SendMessage(const string &pMessage)
    {
        if (nullptr == mMediator) { return; }

        mMediator->SendMessage(pMessage, this);
    }

    void ReceiveMessage(const string &pMessage) { cout << "colleagueA receive message:" << pMessage << endl; }

};

class ColleagueB : public Colleague
{
public:
    void SendMessage(const string &pMessage)
    {
        if (nullptr == mMediator) { return; }

        mMediator->SendMessage(pMessage, this);
    }

    void ReceiveMessage(const string &pMessage) { cout << "colleagueB receive message:" << pMessage << endl; }

};

    static void test_mediator()
    {
        cout << "######################################\n" \
                "##  this is mediator demo...        ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

        ConcreteMediator c1;
        ColleagueA *a_colleague = new ColleagueA();
        a_colleague->SetMediator(&c1);
        ColleagueB *b_colleague = new ColleagueB();
        b_colleague->SetMediator(&c1);
        c1.AddColleague(a_colleague, b_colleague);
        a_colleague->SendMessage("this is send to b colleague.");

        delete a_colleague;
        a_colleague = nullptr;
        delete b_colleague;
        b_colleague = nullptr;
    }

};

#endif //mediator_h
