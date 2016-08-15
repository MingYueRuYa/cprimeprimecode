/****************************************************************************
**
** Copyright (C) 2010 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include <QtCore/QFile>

#include "application.h"

Application::Application(int &argc, char **argv)
	: QApplication(argc, argv)
{
}

Application::~Application()
{
}

bool Application::Initialize()
{
	QFile file(":/black.qss");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		this->setStyleSheet(file.readAll());
	}
	return true;
}

#include "moc_application.cpp"
