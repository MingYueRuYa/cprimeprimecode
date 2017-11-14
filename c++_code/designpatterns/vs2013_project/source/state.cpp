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

#include "state.h"

using std::cout;
using std::endl;
using std::string;

namespace state {

    State::State() {}
    State::~State() {}

    void State::InsertQuarter() {}
    void State::EjectQuarter() {}
    void State::TurnCrank() {}
    void State::Dispense() {}
    void State::Refill() {}
    string State::ToString() { 
        return string(""); 
    }

    HasQuarterState::HasQuarterState(GumballMachine *pGumballMachine) 
        : mGumballMachine(pGumballMachine)
    {
    }

    void HasQuarterState::InsertQuarter() {
        cout << "You can't insert another quarter." << endl;
    }

    void HasQuarterState::EjectQuarter() {
        cout << "Quarter returned" << endl;
        //设置下一个状态
        mGumballMachine->SetState(mGumballMachine->GetNoQuarterState());
    }

    void HasQuarterState::TurnCrank() {
        cout << "You turned..." << endl;
        //设置下一个状态
        int winner = rand()%10;
        if (0 == winner && mGumballMachine->GetGumballCount() > 1) {
            mGumballMachine->SetState(mGumballMachine->GetWinnerState());
        } else {
            mGumballMachine->SetState(mGumballMachine->GetSoldState());
        }
    }

    void HasQuarterState::Dispense() {
        cout << "No gumball dispensed" << endl;
    }

    void HasQuarterState::Refill() {
    }

    string HasQuarterState::ToString() {
        return string("waiting for turn of crank");
    }

    NoQuarterState::NoQuarterState(GumballMachine *pGumballMachine) 
        : mGumballMachine(pGumballMachine)
    {
    }

    void NoQuarterState::InsertQuarter() {
        cout << "You inserted quarter." << endl;
        //设置下一个状态
        mGumballMachine->SetState(mGumballMachine->GetHasQuarterState());
    }

   void NoQuarterState::EjectQuarter() {
        cout << "You haven't inserted quarter." << endl;
    }

    void NoQuarterState::TurnCrank() {
        cout << "You turned, but there's no quarter." << endl;
        //设置下一个状态
    }

    void NoQuarterState::Dispense() {
        cout << "You need to pay first." << endl;
    }

    void NoQuarterState::Refill() {
    }

    string NoQuarterState::ToString() {
        return string("waiting for quarter.");
    }
    

    SoldOutState::SoldOutState(GumballMachine *pGumballMachine) 
        : mGumballMachine(pGumballMachine)
    {
    }

    void SoldOutState::InsertQuarter() {
        cout << "You can't insert a quarter, the machine is sold out" 
             << endl;
        //设置下一个状态
    }

    void SoldOutState::EjectQuarter() {
        cout << "You haven't eject, you haven't inserted a quarter yet." 
             << endl;
    }

    void SoldOutState::TurnCrank() {
        cout << "You turned, but there's no gumballs." << endl;
        //设置下一个状态
    }

    void SoldOutState::Dispense() {
        cout << "No gumball dispensed" << endl;
    }

    void SoldOutState::Refill() {
        mGumballMachine->SetState(mGumballMachine->GetNoQuarterState());
    }

    string SoldOutState::ToString() {
        return string("sold out.");
    }
    
    SoldState::SoldState(GumballMachine *pGumballMachine) 
        : mGumballMachine(pGumballMachine)
    {
    }

    void SoldState::InsertQuarter() {
        cout << "Please wait, we're already giving you a gumball." 
             << endl;
        //设置下一个状态
    }

    void SoldState::EjectQuarter() {
        cout << "Sorry, you already turned the crank" 
             << endl;
    }

    void SoldState::TurnCrank() {
        cout << "Turning twice doesn't get you another gumball." << endl;
    }

    void SoldState::Dispense() {
        mGumballMachine->ReleaseBall();
        if (mGumballMachine->GetGumballCount() > 0) {
            mGumballMachine->SetState(mGumballMachine->GetNoQuarterState());
        } else {
            mGumballMachine->SetState(mGumballMachine->GetSoldOutState());
        }
    }

    void SoldState::Refill() {
    }

    string SoldState::ToString() {
        return string("despending a gumball");
    }

    WinnerState::WinnerState(GumballMachine *pGumballMachine) 
        : mGumballMachine(pGumballMachine)
    {
    }

    void WinnerState::InsertQuarter() {
        cout << "Please wait, we're already giving you a Gumball." 
             << endl;
        //设置下一个状态
    }

    void WinnerState::EjectQuarter() {
        cout << "Sorry, you already turned the crank." 
             << endl;
    }

    void WinnerState::TurnCrank() {
        cout << "Sorry, you already turned the crank." << endl;
    }

    void WinnerState::Dispense() {
        mGumballMachine->ReleaseBall();
        if (mGumballMachine->GetGumballCount() == 0) {
            mGumballMachine->SetState(mGumballMachine->GetSoldOutState());
        } else {
            mGumballMachine->ReleaseBall();
            cout << "YOU'RE A WINNER! You got two gumballs for you quarter."
                 << endl;
            if (mGumballMachine->GetGumballCount() > 0) {
                mGumballMachine->SetState(
                    mGumballMachine->GetNoQuarterState());
            } else {
                cout << "Oops, out of gumballs!" << endl;
                mGumballMachine->SetState(
                    mGumballMachine->GetSoldOutState());
            } // if
        } // if
    }

    void WinnerState::Refill() {
    }

    string WinnerState::ToString() {
        return string("despending two gumballs for your quarter"
                      " , because YOU'RE A WINNER!"); 
    }
       
    GumballMachine::GumballMachine(const int &pNumbersGumball) 
        : mNumberGumball(pNumbersGumball)
    {
        mHasQuarterState = new HasQuarterState(this);
        mNoQuarterState  = new NoQuarterState(this);
        mSoldState       = new SoldState(this);
        mSoldOutState    = new SoldOutState(this);
        mWinnerState     = new WinnerState(this);

        if (mNumberGumball < 0) {
            mCurrentState = mSoldOutState;
        } else {
            mCurrentState = mNoQuarterState;
        }
    }

   GumballMachine::~GumballMachine() {
        if (nullptr != mHasQuarterState) {
            delete mHasQuarterState;
        }

        if (nullptr != mNoQuarterState) {
            delete mNoQuarterState;
        }

        if (nullptr != mSoldOutState) {
            delete mSoldOutState;
        }

        if (nullptr != mSoldState) {
            delete mSoldState;
        }

        if (nullptr != mWinnerState) {
            delete mWinnerState;
        }
    }

    void GumballMachine::ReleaseBall() {
        cout << "A gumball comes rolling out the slot..." << endl;
        if (mNumberGumball != 0) {
            mNumberGumball -= 1;
        }
    }

    void GumballMachine::Refill(const int &pCount) {
        this->mNumberGumball += pCount;
        cout << "The gumball machine  was just refilled;"
                "it's new count is :" << this->mNumberGumball 
             << endl;
    }

    void GumballMachine::InsertQuarter() {
        mCurrentState->InsertQuarter();
    }

    void GumballMachine::EjectQuarter() {
        mCurrentState->EjectQuarter();
    }

    void GumballMachine::TurnCrank() {
        mCurrentState->TurnCrank();
        mCurrentState->Dispense();
    }

    State *GumballMachine::GetHasQuarterState() {
        return mHasQuarterState;
    }

    State *GumballMachine::GetNoQuarterState() {
        return mNoQuarterState;
    }

    State *GumballMachine::GetSoldOutState() {
        return mSoldOutState;
    }

    State *GumballMachine::GetSoldState() {
        return mSoldState;
    }

    State *GumballMachine::GetWinnerState() {
        return mWinnerState;
    }

    void GumballMachine::SetState(State *pState) {
        mCurrentState = pState;
    }

    int GumballMachine::GetGumballCount() { return mNumberGumball; }
    void GumballMachine::SetGumballCount(const int &pCount) { 
        mNumberGumball = pCount;
    }

    string GumballMachine::ToString() {
        string strmsg = "";
        strmsg += "Mighty Gumball, Inc.\n";
        strmsg += "C++ Standing Gumball Model #2004\n";
        strmsg += "Inventory: ";
        strmsg += std::to_string(mNumberGumball);
        if (mNumberGumball != 1) {
            strmsg += "s";
        }
        strmsg += "\n";
        strmsg += "Machine is " + mCurrentState->ToString() + "\n";
        return strmsg;
    }
};

#endif //state_h
