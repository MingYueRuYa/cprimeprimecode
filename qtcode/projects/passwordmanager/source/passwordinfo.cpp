/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDate>
#include <QtXml/QDomDocument>

#include "passwordinfo.h"

PasswordInfo::PasswordInfo(const QString &pPasswordPath)
{
	mUserName   = "";
	mPassword   = "";
    mExtraInfo  = "";
	mUrlAddress = "";
    mPasswordPath = pPasswordPath;
}

PasswordInfo::PasswordInfo(const QString &pUrlAddress, const QString &pUserName, const QString &pPassword, const QString &pExtraInfo, const QString &pPasswordPath)
{
	mUserName   = pUserName;
	mPassword   = pPassword;
    mExtraInfo  = pExtraInfo;
	mUrlAddress = pUrlAddress;
    mPasswordPath = pPasswordPath;
}

PasswordInfo::~PasswordInfo()
{
}
bool PasswordInfo::Save()
{
    QString filename = QDate::currentDate().toString("yyyyMMhhmmss");
    QFile passwordfile(filename + ".xml");
    if (! passwordfile.open(QIODevice::WriteOnly)) {
        passwordfile.close();
        return false;
    }

    QDomDocument passworddom;
    passworddom.appendChild(passworddom.createProcessingInstruction("xml", "version=\"1.0\" enconding=\"UTF-8\""));
    QDomElement passwordelement = passworddom.createElement("passwordinfo");
    passwordelement.setAttribute("UrlAddress", mUrlAddress);
    passwordelement.setAttribute("UserName", mUserName);
    passwordelement.setAttribute("Password", mPassword);
    passwordelement.setAttribute("ExtraInfo", mExtraInfo);
    passworddom.appendChild(passwordelement);

    QTextStream passwordstream(&passwordfile);
    passworddom.save(passwordstream, 4);

    passwordfile.close();
    return true;
}

void PasswordInfo::Delete()
{
}

void PasswordInfo::Modify()
{

}

void PasswordInfo::Load()
{
    //QFile file();
}





