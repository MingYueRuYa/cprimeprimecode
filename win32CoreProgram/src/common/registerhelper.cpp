/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#include "stdafx.h"

#include "registerhelper.h"

#include <stdio.h>

namespace XIBAO
{

RegisterHelper::InnerRegData::InnerRegData()
	:	mKeyName(L""),
		value(L""),
		valueType(0)
{
}

RegisterHelper::InnerRegData::~InnerRegData()
{
}

RegisterHelper::InnerRegData::InnerRegData(const InnerRegData &right)
{
	_CopyValue(right);
}

RegisterHelper::InnerRegData& RegisterHelper::InnerRegData::operator=(
								const InnerRegData &right)
{
	if (this == &right) {
		return *this;
	}
	_CopyValue(right);

	return *this;
}

void RegisterHelper::InnerRegData::_CopyValue(const InnerRegData &right)
{
	this->mKeyName	= right.mKeyName;
	this->value		= right.value;
	this->valueType = right.valueType;
}

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

//bool RegisterHelper::GetValue(const wstring &keyName)
//{
//	return false;
//}

//bool RegisterHelper::SetValue(const wstring &keyName, 
//								const wstring &value, 
//								DWORD regType)
//{
//	HKEY hKey			= 0;
//	DWORD dwSize		= 0;
//	DWORD dwType		= REG_SZ;
//	bool result			= false;
//	wstring strvalue	= value;
//	long lRet			= RegOpenKeyEx(mRootKey, mSubPath.c_str(), 0, 
//								mSamDesired, &hKey);
//	if (lRet == ERROR_SUCCESS) {
//		result = true;
//
//		dwSize	= strvalue.length() * sizeof(TCHAR);
//		lRet	= RegSetValueEx(hKey, keyName.c_str(), 0, dwType, 
//								(const BYTE*)strvalue.c_str(), dwSize);
//		result = lRet == ERROR_SUCCESS ? true : false;
//	} else {
//		if (ERROR_SUCCESS == RegCreateKey(mRootKey, mSubPath.c_str(), &hKey))
//		{
//			result	= true;
//			dwSize	= strvalue.length() * sizeof(TCHAR);
//			lRet	= RegSetValueEx(hKey, keyName.c_str(), 0, 
//								dwType, (const BYTE*)strvalue.c_str(), dwSize);
//			result = lRet == ERROR_SUCCESS ? true : false;
//		}
//	}
//	RegCloseKey(hKey);
//
//	return result;
//}
//
void RegisterHelper::_CopyValue(const RegisterHelper &right)
{
	mRootKey	= right.mRootKey;
	mSubPath	= right.mSubPath;
	mSamDesired = right.mSamDesired;
}

};

