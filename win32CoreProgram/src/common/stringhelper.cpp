/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "stringhelper.h"

#include <stdio.h>
#include <locale>
#include <codecvt>
#include <string>

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


wstring StringHelper::to_wstring(const string &str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

string StringHelper::to_string(const wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wstr);
}

string StringHelper::wstring_to_gbk(const wstring& wstr)
{
	int bufferSize = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	char* buffer = new char[bufferSize];
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, buffer, bufferSize, nullptr, nullptr);
	std::string gbkStr(buffer);
	delete[] buffer;
	return gbkStr;
}
};

