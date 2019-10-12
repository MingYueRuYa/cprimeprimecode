/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "systeminfo.h"

#include <windows.h>

namespace XIBAO {

SystemInfo::SystemInfo()
{
}

SystemInfo::~SystemInfo()
{
}

bool SystemInfo::IsX86()
{
	SYSTEM_INFO si = {0};
    typedef void (WINAPI *LPFN_PGNSI)(LPSYSTEM_INFO);
    LPFN_PGNSI pGNSI = (LPFN_PGNSI)GetProcAddress(
		GetModuleHandleA(("kernel32.dll")), "GetNativeSystemInfo");

    if (pGNSI) { pGNSI(&si); }
	else { return false; }

	return si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? 
												false : true;
}

}

