/****************************************************************************
**
** Copyright (C) 2010 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include <QtGui/QMessageBox>
//#include <QMessageBox>
#include <QtSql/QSqlError>

#include "baseinfo.h"

BaseInfo::BaseInfo()
{
}

BaseInfo::~BaseInfo()
{
}

bool BaseInfo::ExecuteQuery(QSqlQuery &pQuery)
{
	if (! pQuery.exec()) {
		QString message;
		if (pQuery.lastError().isValid()) {
			message = "Database error: " + pQuery.lastError().text();
		}
		else {
			message = "Database error.";
		}
		QMessageBox::warning(0, APPLICATION_NAME, message);
		return false;
	}
	return true;
}

#include "moc_baseinfo.cpp"
