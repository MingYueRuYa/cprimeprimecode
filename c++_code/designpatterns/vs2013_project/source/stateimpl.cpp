/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#include <iostream>

#include "state.h"

using std::cout;
using std::endl;

namespace state
{
	 static void test_state()
    {
        GumballMachine *machine = new GumballMachine(10);
        cout << machine->ToString() << endl;

        machine->InsertQuarter();
        machine->TurnCrank();
        machine->InsertQuarter();
        machine->TurnCrank();
        cout << machine->ToString() << endl;

        machine->InsertQuarter();
        machine->TurnCrank();
        machine->InsertQuarter();
        machine->TurnCrank();
        cout << machine->ToString() << endl;

        machine->InsertQuarter();
        machine->TurnCrank();
        machine->InsertQuarter();
        machine->TurnCrank();
        cout << machine->ToString() << endl;

        machine->InsertQuarter();
        machine->TurnCrank();
        machine->InsertQuarter();
        machine->TurnCrank();
        cout << machine->ToString() << endl;

        machine->InsertQuarter();
        machine->TurnCrank();
        machine->InsertQuarter();
        machine->TurnCrank();
        cout << machine->ToString() << endl;

    }
};