/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
 *  访问者模式：表示一个作用于某对象结构中的各元素的操作，在不改变类的结构下对类的元素增加新的操作
 *  访问者模式是要解决对对象添加新的操作和功能时候，如何尽可能的做到不修改对象的类的一种做法。一般为对象
 *  添加功能，都是给对象增加成员函数。但这里对对象添加了一个统一的接口--accept,来接收一个访问者对象。将对象的操作移动到类外
 *  正式参数visitor的功能。在通过visitor的接口将当前对象指针传递给visitor，就可以拿到当前对象的所有数据，进行操作。
 *  这里涉及到double dispatch概念。第一次将visitor传递给对象，第二次再将当前对象的指针this传递给visitor
 */

#ifndef visitor_h
#define visitor_h

#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

namespace visitor 
{
class Visitor;
class ConcretElementA;
class ConcretElementB;

class Element
{
public:
    Element() = default;
    virtual ~Element() = default;

    virtual void Accept(Visitor *pVisitor) = 0;

};

class Visitor
{
public:
    Visitor() = default;
    virtual ~Visitor() = default;

    virtual void VisitConcretElementA(ConcretElementA *pConcretElementA) = 0;
    virtual void VisitConcretElementB(ConcretElementB *pConcretElementB) = 0;
};

class ConcretElementA : public Element
{
public:
    ConcretElementA() = default;
    virtual ~ConcretElementA() = default;

    void Accept(Visitor *pVisitor)
    {
        pVisitor->VisitConcretElementA(this);
    }

    void OperationA() { cout << "operation A..." << endl; }
};

class ConcretElementB : public Element
{
public:
    ConcretElementB() = default;
    virtual ~ConcretElementB() = default;

    void Accept(Visitor *pVisitor)
    {
        pVisitor->VisitConcretElementB(this);
    }

    void OperationB() { cout << "operation B..." << endl; }
};

class ConcretVisitorA : public Visitor
{
public:
    ConcretVisitorA() = default;
    virtual ~ConcretVisitorA() = default;

    void VisitConcretElementA(ConcretElementA *pConcretElementA)
    {
        cout << "ConcretVisitorA" << endl;
        pConcretElementA->OperationA();
    }

    void VisitConcretElementB(ConcretElementB *pConcretElementB)
    {
        cout << "ConcretVisitorB" << endl;
        pConcretElementB->OperationB();
    }
};

class ConcretVisitorB : public Visitor
{
public:
    ConcretVisitorB() = default;
    virtual ~ConcretVisitorB() = default;

    void VisitConcretElementA(ConcretElementA *pConcretElementA)
    {
        cout << "ConcretVisitorA" << endl;
        pConcretElementA->OperationA();
    }

    void VisitConcretElementB(ConcretElementB *pConcretElementB)
    {
        cout << "ConcretVisitorB" << endl;
        pConcretElementB->OperationB();
    }
};

//管理和遍历元素集合的高层类
class ObjectStruct
{
public:
    ObjectStruct() = default;
    ~ObjectStruct()
    {
        for (list<Element *>::iterator itr = mElementList.begin(); itr != mElementList.end(); ++itr) {
            delete (*itr);
        }
        mElementList.clear();
    }

public:
    void AddElement(Element *pElement)
    {
        mElementList.push_back(pElement);
    }

    void DeleteElement(Element *pElement)
    {
        mElementList.remove(pElement);
    }

    void Display(Visitor *pVisitor) 
    {
        for (auto element : mElementList) {
            element->Accept(pVisitor);
        }
    }

private:
    list<Element *> mElementList;
};

    static void test_visitor()
    {
        cout << "######################################\n" \
                "## this is visitor demo...          ##\n" \
                "##                                  ##\n" \
                "######################################"   \
                << endl;
        
        ObjectStruct obj;
        obj.AddElement(new ConcretElementA());
        obj.AddElement(new ConcretElementA());
        obj.AddElement(new ConcretElementB());
        obj.AddElement(new ConcretElementB());

        Visitor *visitor1 = new ConcretVisitorA();
        Visitor *visitor2 = new ConcretVisitorB();

        obj.Display(visitor1);
        obj.Display(visitor2);
        
        delete visitor1;
        visitor1 = nullptr;
        delete visitor2;
        visitor2 = nullptr;
    }
};

#endif //visitor_h
