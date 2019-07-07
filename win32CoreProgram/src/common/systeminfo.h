/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef systeminfo_h
#define systeminfo_h

namespace XIBAO {

class SystemInfo{
public:
	SystemInfo();
	SystemInfo(const SystemInfo &rhs) = delete;
	~SystemInfo();

	static bool IsX86();

private:
	SystemInfo &operator=(const SystemInfo &) { return *this; }

};

}

#endif // systeminfo_h