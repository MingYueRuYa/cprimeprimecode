/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

#include "application.h"
#include "dbpack.h"
#include "config.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);
	
	if(! Db::Initialize()) {
		QMessageBox::critical(NULL, APPLICATION_NAME, "Error when initialize.");
		return 1;
	}
    MainWindow w;
    w.showMaximized();
    return app.exec();
}
