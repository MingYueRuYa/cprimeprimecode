/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef application_h
#define application_h

#include <QtGui/QApplication>

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
};

#endif //application_h
