/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtCore/QCoreApplication>

#include "userpath.h"
#include "config.h"

bool UserPath::RemovePath(const QDir &pPath)
{
	if (! ClearPath(pPath)) {
		return false;
	}
	//删除本目录夹。
	if (pPath.exists()) {
		if (! pPath.rmdir(pPath.path())) {
            fprintf(stdout, "Error when remove dir %s.\n", pPath.path().toAscii().data());
			return false;
		}
	}
	return true;
}

bool UserPath::ClearPath(const QDir &pPath)
{
	//删除所有子目录。
	QStringList dlist = pPath.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
	QStringListIterator diritr(dlist);
	while (diritr.hasNext()) {
		QString dirname = diritr.next();
		QDir removedir(pPath.filePath(dirname));
		if (! RemovePath(removedir)) {
			return false;
		}
	}
	//删除当前目录夹内的所有文件。
	QStringList flist = pPath.entryList(QDir::Files | QDir::Hidden);
	QStringListIterator fileitr(flist);
	while (fileitr.hasNext()) {
		QString filename = fileitr.next();
		if (QFile::exists(pPath.filePath(filename))) {
			if (! QFile::remove(pPath.filePath(filename))) {
                fprintf(stdout, "Error when remove file %s.\n", pPath.path().toAscii().data());
				return false;
			}
		}
	}
	return true;
}

bool UserPath::CopyPath(const QDir &pSrcPath, const QDir &pDesPath)
{
	if (! pDesPath.exists()) {
		if (! pDesPath.mkpath(pDesPath.path())) {
			return false;
		}
	}
	//复制子目录。
	QStringList dlist = pSrcPath.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
	QStringListIterator diritr(dlist);
	while (diritr.hasNext()) {
		QString dirname = diritr.next();
		QDir srcpath = pSrcPath.path() + "/" + dirname;
		if (srcpath.exists()) {
			if (! CopyPath(srcpath, pDesPath.path() + "/" + dirname)) {
				return false;
			}
		}
	}
	//复制目录下的文件。
	QStringList flist = pSrcPath.entryList(QDir::Files | QDir::Hidden);
	QStringListIterator fileitr(flist);
	while (fileitr.hasNext()) {
		QString filename = fileitr.next();
		if (QFile::exists(pDesPath.filePath(filename))) {
			if (! QFile::remove(pDesPath.filePath(filename))) {
                fprintf(stdout, "Error when remove file %s.\n", pDesPath.filePath(filename).toAscii().data());
				return false;
			}
		}
		if (QFile::exists(pSrcPath.filePath(filename))) {
			if (! QFile::copy(pSrcPath.filePath(filename), pDesPath.filePath(filename))) {
				//fprintf(stdout, "Error when copy file %s.\n", pDesPath.filePath(filename).toAscii().data());
				return false;
			}
		}
	}
	return true;
}

bool UserPath::MovePath(const QDir &pSrcPath, const QDir &pDesPath)
{
	if (! pDesPath.exists()) {
		if (! pDesPath.mkpath(pDesPath.path())) {
			return false;
		}
	}
	//移动子目录。
	QStringList dlist = pSrcPath.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
	QStringListIterator diritr(dlist);
	while (diritr.hasNext()) {
		QString dirname = diritr.next();
		QDir srcpath = pSrcPath.path() + "/" + dirname;
		if (srcpath.exists()) {
			if (! MovePath(srcpath, pDesPath.path() + "/" + dirname)) {
				return false;
			}
		}
	}
	//移动目录下的文件。
	QStringList flist = pSrcPath.entryList(QDir::Files | QDir::Hidden);
	QStringListIterator fileitr(flist);
	while (fileitr.hasNext()) {
		QString filename = fileitr.next();
		if (QFile::exists(pDesPath.filePath(filename))) {
			if (! QFile::remove(pDesPath.filePath(filename))) {
                fprintf(stdout, "Error when remove file %s.\n", pDesPath.filePath(filename).toAscii().data());
				return false;
			}
		}
		if (QFile::exists(pSrcPath.filePath(filename))) {
			if (! QFile::rename(pSrcPath.filePath(filename), pDesPath.filePath(filename))) {
                fprintf(stdout, "Error when move file %s.\n", pDesPath.filePath(filename).toAscii().data());
				return false;
			}
		}
	}
	return true;
}

UserPath::UserPath()
{
#ifdef Q_OS_WIN32
	mUserPath.setPath(QDir::homePath() + "/LinYanFangZhi/" + APPLICATION_NAME);
#endif
#ifdef Q_OS_LINUX
	mUserPath.setPath(QDir::homePath() + "/.LinYanFangZhi/" + APPLICATION_NAME);
#endif
#ifdef Q_OS_MACX
	mUserPath.setPath(QDir::homePath() + "/LinYanFangZhi/" + APPLICATION_NAME);
#endif
	if (! mUserPath.exists()) {
		if (! mUserPath.mkpath(mUserPath.path())) {
			fprintf(stderr, "Error when create user path.\n");
			qApp->quit();
			return;
		}
	}
	mSystemPath = QCoreApplication::applicationDirPath();
}

UserPath::~UserPath()
{
}

QDir UserPath::GetUserPath()
{
	return mUserPath;
}

bool UserPath::IsUserSubPathExists(const QString &pSubPathName)
{
	QDir path(mUserPath.path() + "/" + pSubPathName);
	return path.exists();
}

QDir UserPath::GetUserSubPath(const QString &pSubPathName, bool pCreatePath)
{
	QDir path(mUserPath.path() + "/" + pSubPathName + "/");
	if (! path.exists() && pCreatePath) {
		if (! path.mkpath(path.path())) {
			fprintf(stderr, "Error when create user sub path.\n");
			qApp->quit();
		}
	}
	return path;
}

bool UserPath::RemoveUserSubPath(const QString &pSubPathName)
{
	QDir path(mUserPath.path() + "/" + pSubPathName);
	if (! path.exists()) {
		return true;
	}
	return RemovePath(path);
}

QDir UserPath::GetSystemPath()
{
	return mSystemPath;
}

QDir UserPath::GetSystemSubPath(const QString &pSubPathName)
{
	QDir path(mSystemPath.path() + "/" + pSubPathName + "/");
	return path;
}

#include "moc_userpath.cpp"
