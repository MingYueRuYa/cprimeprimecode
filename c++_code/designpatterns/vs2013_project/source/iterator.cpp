/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
 * 迭代器模式：提供一种方法顺序访问一个聚合对象中各个元素，而又不暴露该对象的内部表示
 *
 */

#ifndef iterator_h
#define iterator_h

#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::string;

namespace iterator
{

#define DELETE_POINT(object) if (nullptr != object) { delete object; object = nullptr; }

class Iterator
{
public:
    Iterator() = default;
    virtual ~Iterator() = default;

    virtual string First() = 0;
    virtual string Next() = 0;
    virtual string GetCurrent() = 0;
    virtual bool IsEnd() = 0;

};

class Aggregate
{
public:
    Aggregate() = default;
    virtual ~Aggregate() = default;
    
    virtual int GetCount() = 0;
    virtual void Push(const string &pValue) = 0;
    virtual string Pop(const int &pIndex) = 0;
    virtual Iterator *CreateIterator() = 0;
};

class ConcretIterator : public Iterator
{
public:
    ConcretIterator(Aggregate *pAggregate) : mAggregate(pAggregate), mCurrentIndex(0) {}
    ~ConcretIterator() = default;

    string First() { return mAggregate->Pop(0); }

    string Next()
    {
        string retval = "";
        if (mCurrentIndex < mAggregate->GetCount()) { 
            retval = mAggregate->Pop(mCurrentIndex); 
            mCurrentIndex++;
        }
        return retval;
    }

    string GetCurrent() { return mAggregate->Pop(mCurrentIndex); }

    bool IsEnd() { return mCurrentIndex == mAggregate->GetCount() ? true : false; }

private:
    Aggregate *mAggregate;    

    int mCurrentIndex;

};

class ConcretAggregate : public Aggregate
{
public:
   ConcretAggregate() : mIterator(nullptr) {}
   ~ConcretAggregate() { DELETE_POINT(mIterator); }

    int GetCount() { return mStrVec.size(); }

    void Push(const string &pValue) { mStrVec.push_back(pValue); }

    string Pop(const int &pIndex) { return mStrVec[pIndex]; }

    Iterator *CreateIterator()
    {
        if (nullptr != mIterator) { return mIterator; }
        
        return mIterator = new ConcretIterator(this);
    }

private:
    Iterator *mIterator;

    vector<string> mStrVec;



};

    static void test_iterator()
    {
        cout << "######################################\n" \
                "##  this is iterator demo...        ##\n" \
                "##                                  ##\n" \
                "######################################"   \
            << endl;
            
        ConcretAggregate *concretaggregate = new ConcretAggregate();
        concretaggregate->Push("linux");
        concretaggregate->Push("unix");
        concretaggregate->Push("freeBSD");

        //这里直接返回一个指针了，暴露出给外部程序，这样不安全。同时这个指针生命周期应该像局部变量，考虑使用shared_ptr智能指针
        Iterator *ite = concretaggregate->CreateIterator();
        
        while (! ite->IsEnd()) {
            cout << ite->Next() << endl;
        }        

    }
};

#endif //iterator_h
