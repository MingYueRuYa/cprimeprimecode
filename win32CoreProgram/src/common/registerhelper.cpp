/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "stdafx.h"

#include "debughelper.h"
#include "registerhelper.h"

#include <stdio.h>

namespace XIBAO
{

RegisterHelper::RegisterHelper(HKEY key, const wstring &subPath, REGSAM regSam)
	:	mRootKey(key),
		mSubPath(subPath),
		mSamDesired(regSam)
{
}

RegisterHelper::RegisterHelper(const RegisterHelper &right)
{
	_CopyValue(right);
}

RegisterHelper& RegisterHelper::operator=(const RegisterHelper &right)
{
	if (this == &right) {
		return *this;
	}

	_CopyValue(right);
	return *this;
}

RegisterHelper::~RegisterHelper()
{
}

DWORD RegisterHelper::SetDWORD(const wstring &keyName, DWORD dwValue)
{
	return SetValue(REG_DWORD, keyName, dwValue);
}

DWORD RegisterHelper::GetDWORD(const wstring &keyName, DWORD &dwValue)
{
	return GetValue(REG_DWORD, keyName, dwValue);
}

DWORD RegisterHelper::SetQWORD(const wstring &keyName, int64_t dwValue)
{
	return SetValue(REG_QWORD, keyName, dwValue);
}

DWORD RegisterHelper::GetQWORD(const wstring &keyName, int64_t &dwValue)
{
	return GetValue(REG_QWORD, keyName, dwValue);
}

DWORD RegisterHelper::SetSZ(const wstring &keyName, const wstring &strValue)
{
	return SetValue(REG_SZ, keyName, strValue);
}

DWORD RegisterHelper::GetSZ(const wstring &keyName, wstring &strValue)
{
	return GetValue(REG_SZ, keyName, strValue);
}

DWORD RegisterHelper::SetMultiSZ(const wstring &keyName, 
									const wstring &strValue)
{
	return SetValue(REG_MULTI_SZ, keyName, strValue);
}

DWORD RegisterHelper::GetMultiSZ(const wstring &keyName, wstring &strValue)
{
	return GetValue(REG_MULTI_SZ, keyName, strValue);
}

DWORD RegisterHelper::SetExpandSZ(const wstring &keyName, 
									const wstring &strValue)
{
	return SetValue(REG_EXPAND_SZ, keyName, strValue);
}

DWORD RegisterHelper::GetExpandSZ(const wstring &keyName, wstring &strValue)
{
	return GetValue(REG_EXPAND_SZ, keyName, strValue);
}

DWORD RegisterHelper::DeleteValue(const wstring &keyName)
{
	if (keyName.empty()) { return -1; }

	HKEY hKey		= 0;
	DWORD errorcode = 0;

	errorcode = RegOpenKeyExW(mRootKey, mSubPath.c_str(), 0, 
											mSamDesired, &hKey);
	if (ERROR_SUCCESS != errorcode) { return errorcode; }
	errorcode = RegDeleteValueW(hKey, keyName.c_str());
	RegCloseKey(hKey);

	return errorcode;
}

DWORD RegisterHelper::DeleteAllValues()
{
	HKEY hKey		= 0;
	DWORD errorcode = 0;

	errorcode = RegOpenKeyExW(mRootKey, mSubPath.c_str(), 0, 
											mSamDesired, &hKey);
	if (ERROR_SUCCESS != errorcode) { return errorcode; }

	errorcode = RegDeleteTreeW(hKey, NULL);
	if (ERROR_SUCCESS != errorcode) { 
		RegCloseKey(hKey);
		return errorcode; 
	}

	RegCloseKey(hKey);
	return errorcode;
}

DWORD RegisterHelper::DeleteKey()
{
	size_t pos = mSubPath.rfind(L"\\");	
	if (wstring::npos == pos) { return -1; }

	wstring partialpath = mSubPath.substr(0, pos);
	wstring keyname		= mSubPath.substr(pos+1, mSubPath.length());

	HKEY hKey = 0;
	DWORD errorcode = RegOpenKeyExW(mRootKey, partialpath.c_str(), 0, 
											mSamDesired, &hKey);
	if (ERROR_SUCCESS != errorcode) { return errorcode; }

	errorcode = RegDeleteKeyExW(hKey, keyname.c_str(), mSamDesired, 0);
	if (ERROR_SUCCESS != errorcode) { 
		RegCloseKey(hKey);
		return errorcode; 
	}

	RegCloseKey(hKey);
	return errorcode;
}

void RegisterHelper::_CopyValue(const RegisterHelper &right)
{
	mRootKey	= right.mRootKey;
	mSubPath	= right.mSubPath;
	mSamDesired = right.mSamDesired;
}

};

