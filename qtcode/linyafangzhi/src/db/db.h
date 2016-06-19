/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef db_h
#define db_h

#include <QtCore/QVariant>
#include <QtCore/QObject>

class Db : public QObject
{
	Q_OBJECT

public:
	static bool Initialize();

	static bool Finalize();

	static void BeginTransaction();

	static void CommitTransaction();

	static void RollbackTransaction();

protected:
	static bool CheckDatabaseVersion();

	static bool CreateAllTables();
};

#endif //db_h
