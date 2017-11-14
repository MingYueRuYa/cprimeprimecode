/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#ifndef state_h_
#define state_h_

#include <string>

using std::string;

namespace state {

class State
{
public:
    State();
    ~State();

    virtual void InsertQuarter();
    virtual void EjectQuarter();
    virtual void TurnCrank();
    virtual void Dispense();
    virtual void Refill();
    virtual string ToString();
};

class GumballMachine
{
public:
    GumballMachine(const int &pNumbersGumball);

    ~GumballMachine();

    void ReleaseBall();

    void Refill(const int &pCount);

    void InsertQuarter();

    void EjectQuarter();

    void TurnCrank();

    State *GetHasQuarterState();

    State *GetNoQuarterState();

    State *GetSoldOutState();

    State *GetSoldState();

    State *GetWinnerState();

    void SetState(State *pState);

    int GetGumballCount();
    void SetGumballCount(const int &pCount);

    string ToString();

private:
    int mNumberGumball;

    State *mHasQuarterState;
    State *mNoQuarterState;
    State *mSoldOutState;
    State *mSoldState;
    State *mWinnerState;

    State *mCurrentState; 
};

class HasQuarterState : public State
{
public:    
    HasQuarterState(GumballMachine *pGumballMachine);

    virtual void InsertQuarter();
    virtual  void EjectQuarter();
    virtual void TurnCrank();
    virtual void Dispense();
    virtual void Refill();
    virtual string ToString();
    
private:
    GumballMachine *mGumballMachine;
};

class NoQuarterState : public State
{
public:    
    NoQuarterState(GumballMachine *pGumballMachine);

    virtual void InsertQuarter();
    virtual  void EjectQuarter();
    virtual void TurnCrank();
    virtual void Dispense();
    virtual void Refill();
    virtual string ToString();
    
private:
    GumballMachine *mGumballMachine;
};

class SoldOutState: public State
{
public:    
    SoldOutState(GumballMachine *pGumballMachine);

    virtual void InsertQuarter();
    virtual void EjectQuarter();
    virtual void TurnCrank();
    virtual void Dispense();
    virtual void Refill();
    virtual string ToString();
    
private:
    GumballMachine *mGumballMachine;
};

class SoldState: public State
{
public:    
    SoldState(GumballMachine *pGumballMachine);

    virtual void InsertQuarter();
    virtual void EjectQuarter();
    virtual void TurnCrank();
    virtual void Dispense();
    virtual void Refill();
    virtual string ToString();
    
private:
    GumballMachine *mGumballMachine;
};

class WinnerState: public State
{
public:    
    WinnerState(GumballMachine *pGumballMachine);

    virtual void InsertQuarter();
    virtual void EjectQuarter();
    virtual void TurnCrank();
    virtual void Dispense();
    virtual void Refill();
    virtual string ToString();
    
private:
    GumballMachine *mGumballMachine;
};

};
#endif //state_h_
