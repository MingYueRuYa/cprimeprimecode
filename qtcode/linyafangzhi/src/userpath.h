/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef userpath_h

#define userpath_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QDir>

/*! \brief common::UserPath
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2008.08.13
	
	用户目录管理，WindowsXP系统下用户目录为：C:/Documents and Settings/Username/PVPLAYER/
*/
class UserPath : public QObject
{
	Q_OBJECT

public:
	/*!
		删除目录以及其子目录。
	*/
	static bool RemovePath(const QDir &pPath);

	/*!
		清空目录以及删除子目录。
	*/
	static bool ClearPath(const QDir &pPath);

	/*!
		复制目录以及其子目录下的所有文件。
	*/
	static bool CopyPath(const QDir &pSrcPath, const QDir &pDesPath);

	/*!
		移动目录以及其子目录下的所有文件。目前该函数会遗留原目录夹下的所有子目录夹。
	*/
	static bool MovePath(const QDir &pSrcPath, const QDir &pDesPath);

	/*!
		构造函数。同时会检查用户目录是否存在，当不存在时自动创建该目录。
	*/
	UserPath();

	/*!
		析构函数。
	*/
	~UserPath();

	/*!
		获取用户目录。
	*/
	QDir GetUserPath();

	/*!
		检查指定的用户子目录是否存在。
	*/
	bool IsUserSubPathExists(const QString &pSubPathName);

	/*!
		获取用户目录下的某个子目录的名称，当该目录不存在时，自动创建。
	*/
	QDir GetUserSubPath(const QString &pSubPathName, bool pCreatePath = true);

	/*!
		删除用户目录下的指定子目录。
	*/
	bool RemoveUserSubPath(const QString &pSubPathName);

	/*!
		获取系统目录，即软件安装的目录。
	*/
	QDir GetSystemPath();

	/*!
		获取系统目录下的某个子目录的名称。
	*/
	QDir GetSystemSubPath(const QString &pSubPathName);

private:
	QDir mUserPath;

	QDir mSystemPath;

};

#endif //userpath_h
