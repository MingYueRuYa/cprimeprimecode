/*
 * about manager user path operation
 * */

#ifndef userpath_h
#define userpath_h
#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtCore/QDir>

class UserPath : public QObject
{
  Q_OBJCET

public:
	/*!
	 * 删除目录以及子目录
	 * */	
	static bool RemovePath(const QDir &pPath, bool pStopFailed);

	/*!
	 * 清空目录以及删除子目录
	 * */	
	static bool ClearPath(const QDir &pPath, bool pStopFailed);

	/*!
	 * 复制目录以及子目录下的所有文件
	 * */	
	static bool CopyPath(const QDir &pSrcPath, const QDir&pDesPath);

	/*!
	 * 移动目录以及子目录下的所有文件。注意：该函数会遗留原目录下的所有子目录
	 * */	
	static bool MovePath(const QDir &pSrcPath, const QDir &pDesPath);	

	/*!
	 * 构造函数。同时会检查用户目录是否存在，当不存在时自动创建该目录
	 * */	
	UserPath();

	~UserPath();

	/*!
	 * 获取用户目录
	 * */	
	QDir GetUserPath() const;	

	/*!
	 * 检查指定的用户子目录是否存在
	 * */	
	bool IsUserSubPathExists(const QString &pSubPathName) const;

	/*!
	 * 获取用户目录下的某个子目录的名称，当该目录不存在，自动创建
	 * */	
	QDir GetUserSubPath(const QString pSubPathName, bool pCreatePath = true) const;

	/*!
	 * 删除用户目录下的指定子目录
	 * */	
	bool RemoveUserSubPath(const QString &pSubPathName) const;

	/*!
	 * 获取系统目录，即软件的安装目录
	 * */	
	QDir GetSystemPath() const;

	/*!
	 * 获取系统目录下的某个子目录的名称
	 * */	
	QDir GetSystemSubPath(const QString &pSubPathName) const;

private:
	QDir mUserPath;

	QDir mSystemPath;
};

#endif //userpath_h
