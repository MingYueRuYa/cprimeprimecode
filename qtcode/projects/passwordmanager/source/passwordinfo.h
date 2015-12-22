/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef passwordinfo_h
#define passwordinfo_h

#include <QtCore/QObject>

/**
  * @brief   about password class
  * @author  liushixiong (635672377@qq.com)
  * @version 0.01
  * @date    2015/12/19
  */
class PasswordInfo : public QObject
{
    Q_OBJECT

public:
    PasswordInfo(const QString &pPasswordPath);

    PasswordInfo(const QString &pUrlAddress, const QString &pUserName, const QString &pPassword, const QString &pExtraInfo, const QString &pPasswordPath);

	~PasswordInfo();

    bool Save();

    void Delete();

    void Modify();

    void Load();

    void SetUrlAddress(const QString &pUrlAddress) { mUrlAddress == pUrlAddress; }

	QString GetUserAddress() { return mUserName; }

	void SetUserName(const QString &pUserName) { mUserName = pUserName; }

	QString GetUserName() { return mUserName; }

	void SetPassword(const QString &pPassword) { mPassword = pPassword;}

	QString GetPassword() { return mPassword; }
	
	void SetExtraInfo(const QString &pExtraInfo) { mExtraInfo = pExtraInfo; }

    QString GetExtraInfo(){ return mExtraInfo; }

private:
	QString mUrlAddress;

	QString mUserName;

	QString mPassword;

    /*!
     * about option information.
     */
	QString mExtraInfo;

    QString mPasswordPath;

};
#endif //passwordinfo_h

