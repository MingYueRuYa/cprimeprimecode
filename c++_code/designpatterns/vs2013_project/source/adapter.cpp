/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com 
** All rights reserved.
**
****************************************************************************/

/*
 * 适配器模式：将类的接口改为用户希望的另外一个接口，解决接口不兼容问题，包括类适配器和对象适配器，一般都用对象适配器
 * 是为了复用以前的代码
 *
 */

#ifndef adapter_h
#define adapter_h

#include <iostream>

using std::cout;
using std::endl;

//stl中deque，queue和satck就是适配器的例子
//deque就是被适配的类
namespace adapter 
{
//双端队列
class Deque
{
public:
    void PushBack(const int &pElement) { cout << "deque push back." << endl; }
    void PushFront(const int &pElement) { cout << "deque push front." << endl; }
    void PopBack() { cout << "deque pop back." << endl; }
    void PopFront() { cout << "deque pop front." << endl; }
};

//顺序容器
class Sequence
{
public:
    virtual void Push(const int &pElement) = 0;
    virtual void Pop() = 0;

protected:
    Deque mDeque;
};

//栈数据结构
class Stack : public Sequence
{
public:
    void Push(const int &pElement) 
    { 
        cout << "stack push..." << endl;
        mDeque.PushBack(pElement);
    }

    void Pop()
    {
        cout << "stack pop..." << endl;
        mDeque.PopBack();
    }
};

//队列数据结构
class Queue : public Sequence
{
public:
    void Push(const int &pElement)
    {
        cout << "queue push..." << endl;
        mDeque.PushBack(pElement);
    }

    void Pop()
    {
        cout << "queue pop..." << endl;
        mDeque.PopFront();
    }
};

static void test_adapter()
{
    cout << "######################################\n" \
            "##  this is adapter demo...         ##\n" \
            "##                                  ##\n" \
            "######################################"   \
            << endl;

    Queue queue;
    queue.Push(1);
    queue.Pop();

    Stack stack;
    stack.Push(2);
    stack.Pop();

}

};

#endif //adapter_h
