/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef xibao_oshelper_h
#define xibao_oshelper_h

#include <string>

using std::wstring;

namespace XIBAO {

/*! \brief common::oshelper
 	\author liushixiong (liushixiongcpp@163.cn)
 	\version 0.01
 	\date 2019-2-23 16:12:04
	\description 获取系统的版本和系统的类型（winxp, win7...）
*/
class OSHelper
{
public:
typedef enum _Version {
	VERSION_PRE_XP = 0,  // Not supported.
	VERSION_XP,
	VERSION_SERVER_2003, // Also includes XP Pro x64 and Server 2003 R2.
	VERSION_VISTA,       // Also includes Windows Server 2008.
	VERSION_WIN7,        // Also includes Windows Server 2008 R2.
	VERSION_WIN8,        // Also includes Windows Server 2012.
	VERSION_WIN8_1,      // Also includes Windows Server 2012 R2.
	VERSION_WIN10,       // Also includes Windows 10 Server.
	VERSION_WIN_LAST,    // Indicates error condition.
} Version;

public:
	static Version GetOSVersion(wstring &OSName);
	static wstring GetOSName();

public:
	OSHelper() = delete;
	~OSHelper() = delete;
	OSHelper &operator=(const OSHelper &rhs) = delete;
	OSHelper(const OSHelper &rhs) = delete;
	OSHelper(OSHelper&& rhs) = delete;

};

};

#endif // xibao_oshelper_h