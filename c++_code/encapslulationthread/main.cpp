/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include "childthread.h"

using namespace std;

int main(int argc, char *argv[])
{
	ChildThread childthread;
	childthread.Start();
	childthread.Stop();

	return 0;
}
