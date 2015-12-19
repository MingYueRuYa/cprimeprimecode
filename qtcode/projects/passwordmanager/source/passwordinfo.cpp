
#include "passwordinfo.h"

PasswordInfo::PasswordInfo()
{
	mUserName   = "";
	mPassword   = "";
    mExtraInfo  = "";
	mUrlAddress = "";
}

PasswordInfo::PasswordInfo(const QString &pUrlAddress, const QString &pUserName, const QString &pPassword, const QString &pExtraInfo)
{
	mUserName   = pUserName;
	mPassword   = pPassword;
    mExtraInfo  = pExtraInfo;
	mUrlAddress = pUrlAddress;
}

PasswordInfo::~PasswordInfo()
{
}

void PasswordInfo::Save()
{

}

void PasswordInfo::Modify()
{

}

void PasswordInfo::Delete()
{
}

void PasswordInfo::Load()
{

}





