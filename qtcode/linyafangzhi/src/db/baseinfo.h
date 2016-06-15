/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef baseinfo_h
#define baseinfo_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtSql/QSqlQuery>

#include "../config.h"

class BaseInfo : public QObject
{
	Q_OBJECT

public:
	BaseInfo();

	~BaseInfo();

	bool ExecuteQuery(QSqlQuery &pQuery);

};

#endif //baseinfo_h
