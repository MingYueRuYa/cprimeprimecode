/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
 * 策略模式： 定义了一系类的算法，把他们封装起来，可以自由替换它们。同时算法的改变不会影响客户端的代码
 * 就是说这些算法的完成的功能是一样，只是实现的上存在差异。
 * 和工厂模式的区别：工厂模式是为了创建一个对象出来。而策略模式对同一方法不同的实现。就是说同样的输入不同的输出效果
 *
 */

#ifndef strategy_h
#define strategy_h

#include <iostream>

using std::cout;
using std::endl;

namespace strategy
{
class ReplaceAlgorithm
{
public:
    virtual void Replace() = 0;
};

class LRU_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
    void Replace()
    {
        cout << "Least recently used replace algorithm." << endl;
    }
};

class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
    void Replace()
    {
        cout << "first in first out replace algorithm." << endl;
    }
};

class Random_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
    void Replace()
    {
        cout << "random replace algorithm." << endl;
    }
};

class Cache
{
public:
    typedef enum _AlgorithmType
    {
        LRU,
        FIFO,
        Random
    }AlgorithmType;

public:
    Cache(ReplaceAlgorithm *pAlogrihtm): mAlogrithm(pAlogrihtm)
    {
    }

    Cache(AlgorithmType pType): mAlogrithm(NULL) //配合简单工厂模式
    {
        if (LRU == pType) {
            mAlogrithm = new LRU_ReplaceAlgorithm();
        } else if (FIFO == pType) {
            mAlogrithm = new FIFO_ReplaceAlgorithm();
        } else if (Random == pType) {
            mAlogrithm = new Random_ReplaceAlgorithm();
        } else {
            mAlogrithm = NULL;
        }
    }

    ~Cache()
    {
        delete mAlogrithm;
        mAlogrithm = NULL;
    }

    void Repalce()
    {
        if (NULL == mAlogrithm) { return; }

        mAlogrithm->Replace();
    }

private:
    ReplaceAlgorithm *mAlogrithm;
};

static void test_strategy()
{
    cout << "######################################\n" \
            "##  this is strategy demo...        ##\n" \
            "##                                  ##\n" \
            "######################################"   \
        << endl;
    
    Cache cache(new LRU_ReplaceAlgorithm()); //这种初始化的方式不好，因为会把所有的算法细节暴露给客户端，违反迪米特法则(最少知道原则)
    cache.Repalce();

    Cache cache1(Cache::FIFO);  //传入一个enum表示算法的种类，客户端不需要知道算法的具体定义是什么
    cache1.Repalce();
}
};

#endif //strategy_h
