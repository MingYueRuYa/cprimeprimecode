/****************************************************************************
**
** Copyright (C) 2010 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include <QtCore/QFile>
#include <QtGui/QFont>

#include "application.h"

#define FONT_SIZE 11

Application::Application(int &argc, char **argv)
	: QApplication(argc, argv)
{
	mChineseSimplifiedTranslator.load("linyafangzhi_zh_CN", ":/i18n");
	qApp->installTranslator(&mChineseSimplifiedTranslator);
	
}

Application::~Application()
{
}

bool Application::Initialize()
{
	this->setFont(QFont("Arial", FONT_SIZE));
	QFile file(":/blue.qss");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		this->setStyleSheet(file.readAll());
	}
	return true;
}

#include "moc_application.cpp"
