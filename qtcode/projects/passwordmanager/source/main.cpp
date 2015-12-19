/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainwindow;

    mainwindow.show();
    return app.exec();
}
