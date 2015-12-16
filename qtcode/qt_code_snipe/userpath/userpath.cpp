
#include "userpath.h"

bool UserPath::RemovePath(const QDir &pPath, bool pStopFailed)
{
  bool result = true;
  if (! ClearPath(pPath, pStopFailed)) {
	result = false;
	if (pStopFailed) {
		return result;
	}
  }
  //删除本目录
  if (pPath.exists()) {
	if (! pPath.rmdir(pPath.path())) {
		fprintf(stdout, "Error where remove dir %s.\n", qPrintable(pPath.path()));
		result = false;
		if (pStopFailed) {
			return result;
	  }
	}
  }
  return result;
}

bool UserPath::ClearPath(const QDir &pPath, bool pStopFailed)
{
	bool result = true;
	//删除所有的子目录
	QStringList dirlist = pPath.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden);
	QStringListIterator dirlistiterator(dirlist);
	while (dirlistiterator.hasNext()) {
		QString dirname = dirlistiterator.next();
		QDir removedir(pPath.filePath(dirname));
		if (! RemovePath(removedir, pStopFailed)) {
			result = false;
			if (pStopFailed) {
				return result;
			}
		}
	}
	//删除当前目录下的所有文件
	QStringList filelist = pPath.entryList(QDir::Files | QDir::Hidden);
	QStringListIterator filelistiterator(filelist);
	while (filelistiterator.hasNext()) {
		QString filename = filelistiterator.next();
		if (File::exists(pPath.filePath(filename))) {
			if (! File::remove(pPath.filePaht(filename))) {
				fprintf(stdout, "Error when remove file %s.\n", qPrintable(pPath.path()));
				result = false;
				if (pStopFailed) {
					return result;
				}
			}	
		}
	}
	return result;
}

bool UserPath::CopyPath(const QDir &pSrcPath, const QDir&pDesPath)
{
  if (! pDesPath.exists()) {
	if (! pDesPath.mkpath(pDesPath.path())) {
		return false;
	}	
  }
  //复制子目录
  QStringList dirlist = pSrcPath.entryList(QDir::AllDirs | QDir::NotDotAndDotDot | QDir::Hidden);
  QStringListIterator dirlistiterator(dirlist);
  while (dirlistiterator.hasNext()) {
	QString dirname = dirlistiterator.next();
	QDir srcpath = pSrcPath.path() + "/" + dirname;
	if (srcpath.exists()) {
		if (! CopyPath(srcpath, pDesPath.path() + "/" + dirname)) {
			return false;
		}
	}
  }
  //复制目录下的文件
  QStringList filelist = pSrcPath.entryList(QDir::Files | QDir::Hidden);
  QStringListIterator filelistiterator(filelist); 
  while (filelistiterator.hasNext()) {
	QString filename = filelistiterator.next();
	//如果pDesPath中存在相同的文件，先删除
	if (QFile::exists(pDesPath.filePath(filename))) {
	  if (! QFile::remove(pDesPath.filePath(filename))) {
		fprintf(stdout, "Error when remove file %s.\n", qPrintable(pDesPath.filePath(filename)));	
	  }
	}
	if (QFile::exists(pDesPath.filePath(filename))) {
		if (! QFile::copy(pSrcPath.filePath(filename), pDesPath.filePath(filename))) {
			fprintf(stdout, "Error when copy file %s.\n", qPrintable(pDesPath.filePath(filename));
		}
	}	
  }
}

bool UserPath::MovePath(const QDir &pSrcPath, const QDir &pDesPath)
{}

UserPath::UserPath()
{}

UserPath::~UserPath()
{}

QDir UserPath::GetUserPath() const	
{}

bool UserPath::IsUserSubPathExists(const QString &pSubPathName) const
{}

QDir UserPath::GetUserSubPath(const QString pSubPathName, bool pCreatePath = true) const
{}

bool UserPath::RemoveUserSubPath(const QString &pSubPathName) const
{}

QDir UserPath::GetSystemPath() const
{}

