/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com (http://www.2144.cn)
** All rights reserved.
**
****************************************************************************/

// 2018年 01月 06日 星期六 21:46:53 CST

#include <iostream>
#include <map>

#include "designpatternpack.h"

using std::cout;
using std::endl;
using std::cin;
using std::map;

typedef std::function<void()> funptr;

map<int, funptr> g_map;

void InitMap()
{
    g_map[1] = std::bind(simple_factory::test_simple_factory);
    g_map[2] = std::bind(factory::test_factory);
    g_map[3] = std::bind(abstract_factory::test_abstract_factory);
    g_map[4] = std::bind(strategy::test_strategy);
    g_map[5] = std::bind(adapter::test_adapter);
    g_map[6] = std::bind(prototype::test_prototype);
    g_map[7] = std::bind(template_method::test_template_method);
    g_map[8] = std::bind(builder::test_builder);
    g_map[9] = std::bind(facade::test_facade);

    g_map[10] = std::bind(composite::test_composite);
    g_map[11] = std::bind(proxy::test_proxy);
    g_map[12] = std::bind(flyweight::test_flyweight);
    g_map[13] = std::bind(bridge::test_bridge);
    g_map[14] = std::bind(mediator::test_mediator);
    g_map[15] = std::bind(
                        chain_of_responsibility::test_chain_of_responsibility);
    g_map[16] = std::bind(observer_event::test_observer_event);
    g_map[17] = std::bind(template_method::test_template_method);
    g_map[18] = std::bind(memento::test_memento);
    g_map[19] = std::bind(state::test_state);
    g_map[20] = std::bind(command::test_command);
    g_map[21] = std::bind(iterator::test_iterator);
    g_map[22] = std::bind(visitor::test_visitor);
}

void Print()
{
    cout << "(0) " << "exit..." << endl;
    cout << "(1) " << "simple_factory::test_simple_factory" << endl;
    cout << "(2) " << "factory::test_factory"               << endl;
    cout << "(3) " << "abstract_factory::test_abstract_factory" << endl;
    cout << "(4) " << "strategy::test_strategy"             << endl;
    cout << "(5) " << "adapter::test_adapter"               << endl;
    cout << "(6) " << "prototype::test_prototype"           << endl;
    cout << "(7) " << "template_method::test_template_method" << endl;
    cout << "(8) " << "builder::test_builder"       << endl;
    cout << "(9) " << "facade::test_facade"         << endl;
    cout << "(10) " << "composite::test_composite"  << endl;

    cout << "(11) " << "proxy::test_proxy"          << endl;
    cout << "(12) " << "flyweight::test_flyweight"  << endl;
    cout << "(13) " << "bridge::test_bridge"        << endl;
    cout << "(14) " << "mediator::test_mediator"    << endl;
    cout << "(15) " 
         << "chain_of_responsibility::test_chain_of_responsibility" << endl;
    cout << "(16) " << "observer_event::test_observer_event"        << endl;
    cout << "(17) " << "template_method::test_template_method"      << endl;
    cout << "(18) " << "memento::test_memento"      << endl;
    cout << "(19) " << "state::test_state"          << endl;
    cout << "(20) " << "command::test_command"      << endl;
    cout << "(21) " << "iterator::test_iterator"    << endl;
    cout << "(22) " << "visitor::test_visitor"      << endl;
}

int main(int argc, char *argv[])
{
    InitMap();

    Print();

    int index = 0;
    while (1) {
        cin >> index;
        if (0 == index) {
            break;
        }
        funptr fun = g_map[index];
        if (NULL == fun) {
            cout << "please input 1-22 index" << endl;
        } else {
            fun();
        }
        cout << "----------------------------------------------" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "----------------------------------------------" << endl;
        Print();
    }
 
    return 0;
}
