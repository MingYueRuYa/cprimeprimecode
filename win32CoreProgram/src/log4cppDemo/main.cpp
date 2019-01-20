/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "log4cpphelper.h"

using XIBAO::Log4cppHelper;

int wmain(int argc, wchar_t *argv[])
{
	LOG_INITIALIZE("log4cppdemo");

	LOG_ERROR("error....");

	LOG_ERROR_ARGS("%s-%d", "main", 166);

	return 0;
}