/****************************************************************************
**
** Copyright (C) 2010 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#ifndef baseinfo_h
#define baseinfo_h

#include <QtCore/QVariant>
#include <QtCore/QObject>
#include <QtSql/QSqlQuery>

#include "../config.h"

/*! \brief BaseInfo
 	\author tony (tonixinot@gmail.com)
 	\version 0.01
 	\date 2010.11.07
 	
	各类数据库存储类基类。
*/
class BaseInfo : public QObject
{
	Q_OBJECT

public:
	BaseInfo();

	~BaseInfo();

	bool ExecuteQuery(QSqlQuery &pQuery);

};

#endif //baseinfo_h
