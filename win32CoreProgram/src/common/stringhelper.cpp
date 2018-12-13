/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "stdafx.h"

#include "stringhelper.h"

#include <stdio.h>

namespace XIBAO
{

string StringHelper::FormatString(LPCSTR format, ...)
{
	va_list args;
	va_start(args, format);
	int len = _vscprintf(format, args) + 1;
	va_end(args);

	va_start(args, format);
	char *buf = new char[len];
	_vsnprintf_s(buf, len, len, format, args);
	va_end(args);

	string formatstr(buf, len-1);
	delete[] buf;
	return formatstr;
}

wstring StringHelper::FormatString(LPCTSTR format, ...)
{
	va_list args;
	va_start(args, format);
	int len = _vscwprintf(format, args) + 1;
	va_end(args);

	va_start(args, format);
	wchar_t *buf = new wchar_t[len];
	_vsnwprintf_s(buf, len, len, format, args);
	va_end(args);

	wstring formatstr(buf, len - 1);
	delete[] buf;
	return formatstr;
}

};

