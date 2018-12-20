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

