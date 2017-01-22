/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include "strvec.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	//StrVec strvec("linux", "unix", "Arch linux");
	StrVec strvec{"linux", "unix", "Arch linux"};
	strvec.Foreach();
	strvec.PushBack("FreeBSD");
	strvec.Foreach();
	return 0;
}

