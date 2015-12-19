

#ifndef passwordinfo_h
#define passwordinfo_h

#include <QString>

class PasswordInfo
{
public:
	PasswordInfo();

	PasswordInfo(const QString &pUrlAddress, const QString &pUserName, const QString &pPassword, const QString &pExtraInfo);

	~PasswordInfo();

    void Save();

    void Modify();

    void Delete();

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

	QString mExtraInfo;

};
#endif //passwordinfo_h

