/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 状态模式：允许一个对象在内部状态发生变化时影响其行为
*   和责任链模式很相似，但是状态模式维护的一个条状态链，类似状态机的模式
*
*/

#ifndef state_h
#define state_h

#include <iostream>
#include <string>
using std::cout;
using std::endl;

using std::string;

namespace state
{
class War;    

class State
{
public:
    State() = default;
    virtual ~State() = default;

    virtual void Prophase() {}

    virtual void Metaphase() {}

    virtual void Anaphase() {}

    virtual void End() {}

    virtual void CurrentState(War *pWar) {}

};

class War
{
public:
    War(State *pState) : mState(pState), mDays(0) {}
    ~War() 
    {
        if (nullptr == mState) { return; }
        delete mState;
        mState = nullptr;
    }

    int GetDays() const { return mDays; }
    void SetDays(const int &pDays) { mDays = pDays; }

    void SetState(State *pState)
    {
        if (nullptr != mState) {
            delete mState;
            mState = nullptr;
        }

        mState = pState;
    }

    void GetState() { mState->CurrentState(this); }

private:
    State *mState;
    
    int mDays;  //战争持续的时间

};

class EndState : public State //战争结束
{
public:
    EndState() = default;
    ~EndState() = default;

    void End(War *pWar) { cout << "war is end." << endl; }

    void CurrentState(War *pWar) { End(pWar); }
};

class AnaphaseState : public State
{
public:
    AnaphaseState() = default;
    ~AnaphaseState() = default;

    void Anaphase(War *pWar)
    {
        if (pWar->GetDays() < 30) { cout << "the " << pWar->GetDays() << " day " << "anaphase." << endl;}
        else {
            pWar->SetState(new EndState());
            pWar->GetState();
        }
    }

    void CurrentState(War *pWar) { Anaphase(pWar); }

};

class MetaphaseState : public State
{
public:
    MetaphaseState() = default;
    ~MetaphaseState() = default;

    void Metaphase(War *pWar)
    {
        if (pWar->GetDays() < 20)  { cout << "the " << pWar->GetDays() << " day " << "metaphase." << endl;}
        else {
            pWar->SetState(new AnaphaseState());
            pWar->GetState();
        }
    }

    void CurrentState(War *pWar) { Metaphase(pWar); };

};

class ProphaseState : public State
{
public:
    ProphaseState() = default;
    ~ProphaseState() = default;

    void prophase(War *pWar)
    {
        if (pWar->GetDays() < 10) { cout << "the " << pWar->GetDays() << " day " << " prophase." << endl;}
        else {
            pWar->SetState(new MetaphaseState());
            pWar->GetState();
        }
    }
    
    void CurrentState(War *pWar) { prophase(pWar); }
};

    static void test_state()
    {
        cout << "######################################\n" \
                "##  this is state demo...           ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

        War *war = new War(new ProphaseState());

        for (int i=0; i<40; ++i) {
            war->SetDays(i);
            war->GetState();
        }

        delete war;
        war = nullptr;
    }

};

#endif //state_h
