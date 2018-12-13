#include "stdafx.h"

#include "debughelper.h"

#include <stdio.h>

namespace XIBAO
{

void DebugHelper::OutputDebugString(LPCSTR format, ...)
{
	va_list args;
	va_start(args, format);
	int len = _vscprintf(format, args) + 1;
	va_end(args);

	va_start(args, format);
	char *buf = new char[len];
	_vsnprintf_s(buf, len, len, format, args);
	va_end(args);

	::OutputDebugStringA(buf);
	delete[] buf;
}

void DebugHelper::OutputDebugString(LPCTSTR format, ...)
{
	va_list args;
	va_start(args, format);
	int len = _vscwprintf(format, args) + 1;
	va_end(args);

	va_start(args, format);
	wchar_t *buf = new wchar_t[len];
	_vsnwprintf_s(buf, len, len, format, args);
	va_end(args);

	::OutputDebugString(buf);
	delete[] buf;
}

void DebugHelper::OutputDebugString(const wstring &strbufinfo)
{
	::OutputDebugString(strbufinfo.c_str());
}

void DebugHelper::OutputDebugString(const string &strbufinfo)
{
	::OutputDebugStringA(strbufinfo.c_str());
}

} //namespace XIBAO;

