/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include "basethread.h"

using std::cout;
using std::endl;

BaseThread::BaseThread()
{
	cout << "BaseThread..." << endl;
}

BaseThread::~BaseThread()
{
	cout << "~BaseThread..." << endl;
}

void BaseThread::Start()
{
}

void BaseThread::Stop()
{
}

void BaseThread::Run()
{
}
