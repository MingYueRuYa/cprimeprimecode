/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef stringhelper_h
#define stringhelper_h

#include <string>
#include <windows.h>

using std::string;
using std::wstring;

namespace XIBAO {

/*! \brief common::stringhelper
 	\author liushixiong (liushixiongcpp@163.cn)
 	\version 0.01
	\description ×Ö·û´®´¦Àíº¯Êý
 	\date 2018-11-29 10:58:13
*/
class StringHelper
{
public:	
	StringHelper() = default;
	~StringHelper() = default;
	StringHelper(const StringHelper &) = default;

	static string FormatString(LPCSTR format, ...);
	static wstring FormatString(LPCTSTR format, ...);

	static wstring to_wstring(const string &str);
	static string to_string(const wstring &str);
	static string wstring_to_gbk(const wstring &str);

};

};

#endif // stringhelper_h