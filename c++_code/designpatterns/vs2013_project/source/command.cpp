/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
*	command: 将一个请求封装为一个对象，从而可以不同的请求参数化对客户进行参数化
*		例如：请求排队或记录日志，以及支持可撤销的操作
*/

#ifndef command_h
#define command_h

#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::string;

namespace command
{
#define DELETE_POINT(object) if (nullptr != object) { delete object; object = nullptr; }

class Command;

class Barbecur
{
public:
    Barbecur() = default;
    ~Barbecur() = default;

public:
    void BakeMutton() { cout << "Bake mutton" << endl; }
    void BakeChickenWing() { cout << "Bake chicken wing" << endl; }

};

class Command
{
public:
	Command(Barbecur *pBarbecur) : mBarbecur(pBarbecur) {}
	virtual ~Command() =default;
	
	virtual void Execute() = 0;

protected:
    Barbecur *mBarbecur;

};

class BakeMuttonCommand : public Command
{
public:
    BakeMuttonCommand(Barbecur *pBarbecur) : Command(pBarbecur) {}
    ~BakeMuttonCommand() = default;

    void Execute() 
    {
        if (nullptr == mBarbecur) { return; }

        mBarbecur->BakeMutton(); //更多的定制化需求，比如不要孜然，7分熟
    }

};

class BakeChickenWingCommand : public Command
{
public:
    BakeChickenWingCommand(Barbecur *pBarbecur) : Command(pBarbecur) {}
    ~BakeChickenWingCommand() = default;

    void Execute() 
    {
        if (nullptr == mBarbecur) { return; }

        mBarbecur->BakeChickenWing(); //更多的定制化需求，比如不要孜然，7分熟
    }

};

class Waiter
{
public:
    Waiter() = default;
    ~Waiter() = default;

    void SetOrder(Command *pCommand)
    {
        mVector.push_back(pCommand);
    }

    void Notify()
    {
        for (auto bakecommand : mVector) {
            bakecommand->Execute(); 
        }
    }

private:
    vector<Command *>mVector;
};

    static void test_command()
    {
        cout << "######################################\n" \
                "##  this is command demo...         ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

        Barbecur *barbecur = new Barbecur();

        BakeMuttonCommand 		*muttoncommand 	= new BakeMuttonCommand(barbecur);
        BakeChickenWingCommand 	*chickencommand = new BakeChickenWingCommand(barbecur);

        Waiter *waiter = new Waiter();
        waiter->SetOrder(muttoncommand);
        waiter->SetOrder(chickencommand);
        waiter->Notify();        

        DELETE_POINT(barbecur);
        DELETE_POINT(muttoncommand);
        DELETE_POINT(chickencommand);
        DELETE_POINT(waiter);
    }
};

#endif //command_h