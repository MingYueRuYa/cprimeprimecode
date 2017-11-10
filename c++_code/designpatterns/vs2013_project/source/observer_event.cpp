/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 观察者模式：定义对象间一对多的依赖关系。当一个对象的状态发生变化，所有依赖于它的对象都得到通知并做出响应的动作。
*
*/

#ifndef observer_event_h
#define observer_event_h

#include <list>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::list;
using std::string;

namespace observer_event
{
class Observer
{
public:
    Observer() = default;

    virtual ~Observer() = default;

    virtual void Update() {}

};

class Blog
{
public:
    Blog() = default;

    virtual ~Blog() = default;

    void Attach(Observer *pObserver)  { mObserverList.push_back(pObserver); } //添加观察者

    void Remove(Observer *pObserver) { mObserverList.remove(pObserver); } //移除观察者

    void Notify()
    {
        for (Observer *obs : mObserverList) {
            obs->Update();
        }
    }

    virtual void SetStatus(const string &pStatus) { Notify(); }

protected:
    list<Observer *> mObserverList;

};

class ObserverBlog : public Observer
{
public:
    ObserverBlog() = default;
    ~ObserverBlog() = default;

    void Update()
    {
        cout << "observer blog..." << endl;
    }
};

class ObserverBlogA : public Observer
{
public:
    ObserverBlogA() = default;
    ~ObserverBlogA() = default;

    void Update()
    {
        cout << "observer blog A..." << endl;
    }
};

    static void test_observer_event()
    {
        cout << "######################################\n" \
                "## this is observer event demo...   ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

        ObserverBlog *b1  = new ObserverBlog();
        ObserverBlogA *b2 = new ObserverBlogA();
        
        Blog *blog = new Blog();
        blog->Attach(b1);
        blog->Attach(b2);
        blog->SetStatus("");
        delete blog, b1, b2;
        blog = nullptr;
        b1   = nullptr;
        b2   = nullptr;
    }

};

#endif //observer_event_h
