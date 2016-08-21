/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef application_h
#define application_h

#include <QtGui/QApplication>
#include <QtCore/QTranslator>

#include "config.h"

class Application : public QApplication
{
	Q_OBJECT

public:
	Application(int &argc, char **argv);

	~Application();

	/*!
		初始化系统。
	*/
	bool Initialize();

private:
	QTranslator mChineseSimplifiedTranslator;
};

#endif //application_h
