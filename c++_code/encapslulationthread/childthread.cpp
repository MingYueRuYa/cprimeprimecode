/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include "childthread.h"

using std::cout;
using std::endl;

ChildThread::ChildThread()
{
}

ChildThread::~ChildThread()
{
}

void ChildThread::Execute()
{
	cout << "this test thread..." << endl;
}
