/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "db.h"
#include "orderinfo.h"
#include "../userpath.h"

#define DATABASE_FILENAME "linyafangzhi.db"
#define DATABASE_VERSION "160619"

bool Db::Initialize()
{
	UserPath userpath;
	QString filename = userpath.GetUserPath().filePath(DATABASE_FILENAME);
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(filename);
	if (! db.open()) {
		return false;
	}
	bool recreatedb = false;
	if (! QFile::exists(filename)) {
		recreatedb = true;
	}
	if (! recreatedb && ! CheckDatabaseVersion()) {
		recreatedb = true;
	}
	if (recreatedb) {
		db.close();
		if (QFile::exists(filename)) {
			if (! QFile::remove(filename)) {
				return false;
			}
		}
		if (! db.open()) {
			return false;
		}
		if (! CreateAllTables()) {
			return false;
		}
	}
	return true;
}

bool Db::Finalize()
{
	QSqlDatabase::database().close();
	return true;
}

void Db::BeginTransaction()
{
	QSqlDatabase::database().transaction();
}

void Db::CommitTransaction()
{
	QSqlDatabase::database().commit();
}

void Db::RollbackTransaction()
{
	QSqlDatabase::database().rollback();
}

bool Db::CheckDatabaseVersion()
{
	QSqlQuery query;
	query.prepare("SELECT value FROM system WHERE name='version'");
	if (! query.exec()) {
		return false;
	}
	if (! query.next()) {
		return false;
	}
	QString version = query.value(0).toString();
	if (version.compare(DATABASE_VERSION) != 0) {
		return false;
	}
	return true;
}

bool Db::CreateAllTables()
{
	QSqlQuery query;
	query.prepare("CREATE TABLE system ("
		"name VARCHAR,"
		"value VARCHAR)");
	if (! query.exec()) {
		return false;
	}
	query.prepare("INSERT INTO system VALUES (:name, :value)");
	query.bindValue(":name", "version");
	query.bindValue(":value", DATABASE_VERSION);
	if (! query.exec()) {
		return false;
	}
	if (! OrderInfo::CreateTable()) {
		return false;
	}
	return true;
}

#include "moc_db.cpp"
