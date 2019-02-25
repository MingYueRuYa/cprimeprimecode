/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "oshelper.h"

#include <windows.h>
#include <versionhelpers.h>

#pragma warning(disable: 4996) 

namespace XIBAO
{

OSHelper::Version OSHelper::GetOSVersion(wstring &OSName)
{
	Version version_ = VERSION_XP;
	OSVERSIONINFOEX version_info = { sizeof version_info };
	// 这个函数在8.1之后不能正常使用
	// 正常识别win8.1 需要将当前目录下的compatibility.xml，加入到应用程序的清单文件
	// 项目-》属性-》清单工具-》输入和输出-》附加清单文件
	::GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&version_info));
	if ((version_info.dwMajorVersion == 5) && (version_info.dwMinorVersion>0)) {
		// Treat XP Pro x64, Home Server, and Server 2003 R2 as Server 2003.
		version_ = (version_info.dwMinorVersion == 1) ? 
						VERSION_XP : VERSION_SERVER_2003;
		if (VERSION_PRE_XP == version_) {
			OSName = L"windows XP";
		} else {
			OSName = L"windows server 2003";
		}
	}
	else if (version_info.dwMajorVersion == 6) {
		switch (version_info.dwMinorVersion) {
		case 0:
			// Treat Windows Server 2008 the same as Windows Vista.
			version_	= VERSION_VISTA;
			OSName		= L"windows vista";
			break;
		case 1:
			// Treat Windows Server 2008 R2 the same as Windows 7.
			version_ = VERSION_WIN7;
			OSName		= L"windows 7";
			break;
		case 2:
			// Treat Windows Server 2012 the same as Windows 8.
			version_ = VERSION_WIN8;
			OSName		= L"windows 8";
			break;
		default:
			version_ = VERSION_WIN8_1;
			OSName		= L"windows 8.1";
			break;
		}
	}
	else if (version_info.dwMajorVersion == 10) {
		version_ = VERSION_WIN10;
		OSName		= L"windows 10";
	}
	else if (version_info.dwMajorVersion > 6) {
		version_	= VERSION_WIN_LAST;
		OSName		= L"windows last";
	}
	return version_;
}

wstring OSHelper::GetOSName()
{
	wstring osname = L"unkown operator system";
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	OSVERSIONINFOEXW versioninfo;
	ZeroMemory(&versioninfo, sizeof(OSVERSIONINFOEXW));
	versioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
	
	// 这个函数在8.1之后不能正常使用
	// 正常识别win8.1 需要将当前目录下的compatibility.xml，加入到应用程序的清单文件
	// 项目-》属性-》清单工具-》输入和输出-》附加清单文件
	if (! ::GetVersionExW(reinterpret_cast<OSVERSIONINFO *>(&versioninfo))) {
		return osname;
	}

	switch (versioninfo.dwMajorVersion)
	{
	case 4: //
	{
		switch (versioninfo.dwMinorVersion)
		{
		case 0:
		{
			if (versioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
				osname = L"Microsoft Windows NT 4.0"; //1996年7月发布   
			else if (versioninfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
				osname = L"Microsoft Windows 95";
		}
		break;
		case 10:
		{
			osname = L"Microsoft Windows 98";
		}
		break;
		case 90:
		{
			osname = L"Microsoft Windows Me";
		}
		break;
		}
	}
	break;
	case 5:
	{
		switch (versioninfo.dwMinorVersion)
		{
		case 0:
		{
			osname = L"Microsoft Windows 2000";
		}
		break;
		case 1:
		{
			osname = L"Microsoft Windows XP";
		}
		break;
		case 2:
		{
			if (versioninfo.wProductType == VER_NT_WORKSTATION
				&& info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
			{
				osname = L"Microsoft Windows XP Professional x64 Edition";
			}
			else if (GetSystemMetrics(SM_SERVERR2) == 0)
				osname = L"Microsoft Windows Server 2003";//2003年3月发布   
			else if (GetSystemMetrics(SM_SERVERR2) != 0)
				osname = L"Microsoft Windows Server 2003 R2";
		}
		break;
		}
	}
	break;
	case 6:
	{
		switch (versioninfo.dwMinorVersion)
		{
		case 0:
		{
			if (versioninfo.wProductType == VER_NT_WORKSTATION)
				osname = L"Microsoft Windows Vista";
			else
				osname = L"Microsoft Windows Server 2008";//服务器版本   
			break;
		}
		break;
		case 1:
		{
			if (versioninfo.wProductType == VER_NT_WORKSTATION)
				osname = L"Microsoft Windows 7";
			else
				osname = L"Microsoft Windows Server 2008 R2";
			break;
		}
		break;
		case 2:
		{
			HMODULE hm;
			DWORD dwMajorVersion = 0, dwMinorVersion = 0, dwOptionalBuild = 0;
			if (hm = LoadLibrary(L"ntdll.dll"))
			{

				typedef void (WINAPI *getver)(DWORD*, DWORD*, DWORD*);
				getver gv;
				gv = (getver)GetProcAddress(hm, "RtlGetNtVersionNumbers");
				if (gv)
				{
					gv(&dwMajorVersion, &dwMinorVersion, &dwOptionalBuild);
				}

				FreeLibrary(hm);
			}
			if (dwMajorVersion == 10)
			{
				osname = L"Microsoft Windows 10";
			}
			else
			{
				if (versioninfo.wProductType == VER_NT_WORKSTATION)
					osname = L"Microsoft Windows 8";
				else
					osname = L"Microsoft Windows Server 2012";
			}
		}
		break;
		case 3:
		{
			if (versioninfo.wProductType == VER_NT_WORKSTATION)
				osname = L"Microsoft Windows 8.1";
			else
				osname = L"Microsoft Windows Server 2012 R2";
			break;
		}
		break;
		}
	}
	break;
	case 10:
	{
		switch(versioninfo.dwMinorVersion) 
		{
		case 0:
			if (versioninfo.wProductType == VER_NT_WORKSTATION)
				osname = L"Microsoft Windows 10";
			else
				osname = L"Microsoft Windows Server 2016";
			break;
		defualt:
			break;
		}
	}
	break;
	default:
		break;
	}
	return osname;
}

};