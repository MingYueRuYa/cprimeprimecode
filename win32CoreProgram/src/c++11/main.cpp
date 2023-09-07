/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#include <iostream>
#include "thread.cpp"
#include "lvalue.h"
#include "stl_function.h"
#include "message_bus.hpp"

#include <list>

using std::cout;
using std::endl;
using std::list;

// #define TEST_RIGHT_REFRENCE

void test_msg_bus()
{
    MessageBus msgbus;
    msgbus.Attach([](int a) { std::cout << "no reference" << a << std::endl; });
    msgbus.Attach([](int& a) { std::cout << "left reference" << a << std::endl; });
    msgbus.Attach([](int&& a) { std::cout << "right reference" << a << std::endl; });
    msgbus.Attach([](const int& a) { std::cout << "const left reference" << a << std::endl; });
    msgbus.Attach([](int a) { std::cout << "no reference has reture value and key" << a << std::endl; return a; }, "a");

    int i = 2;

    msgbus.SendReq<void, int>(2);
    msgbus.SendReq<int, int>(2, "a");
    msgbus.SendReq<void, int &>(i);
    msgbus.SendReq<void, const int &>(2);
    msgbus.SendReq<void, int &&>(2);


    msgbus.Remove<void, int>();
    msgbus.Remove<int, int>();
    msgbus.Remove<void, int &>();
    msgbus.Remove<void, const int&>();
    msgbus.Remove<void, int&&>();

    msgbus.SendReq<void, int>(2);
    msgbus.SendReq<int, int>(2, "a");
    msgbus.SendReq<void, int &>(i);
    msgbus.SendReq<void, const int &>(2);
    msgbus.SendReq<void, int &&>(2);
}



int main(void)
{

#ifdef TEST_RIGHT_REFRENCE
	// LValue::TestRValueFun();
	// class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > &
	// class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >

	// LValue::TestCopyCon01();
	//constructor 1
	//constructor 2
	//copy constructor
	//~dtor 2
	//~dtor 1
	//~dtor 1
	// -------------------add ”“÷µøΩ±¥
	//constructor 1
	//constructor 2
	//move constructor
	//~dtor
	//~dtor
	//~dtor

	// LValue::TestForwardFun();
	// left value
	// right value
	// right value
	// left value
	// left value
	// right value
	// left value
	// right value
	// right value

	// LValue::TestFuncWrapperFunc();
	// void
	// 1
	// 2
	// abcdef

	LValue::TestEmplaceFunc();
	// --insert--
	// is constructed
	// is moved
	// is moved
	// --emplace--
	// is constructed
	// is moved
	// --emplace back--
	// is constructed
	// --puch back--
	// is constructed
	// is moved
	// is moved

#endif // TEST_RIGHT_REFRENCE

    stl_function::test_function1();
    stl_function::test_function2();
    stl_function::test_my_func();


    test_msg_bus();

	system("pause");
	return 0;
}