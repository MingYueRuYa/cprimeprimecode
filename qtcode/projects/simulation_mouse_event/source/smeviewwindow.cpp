/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include "smeviewwindow.h"

smeViewWindow::smeViewWindow(QWidget *pParent)
{
	setWindowOpacity(0.5);
}

smeViewWindow::~smeViewWindow()
{
}

void smeViewWindow::mousePressEvent(QMouseEvent *pMouseEvent)
{
	int xposition = pMouseEvent->globalX();
	int yposition = pMouseEvent->globalY();
	emit OnUpdatePosition(xposition, yposition);
	setWindowTitle(QString::number(xposition) + "," + QString::number(yposition));
}

void smeViewWindow::closeEvent(QCloseEvent *pCloseEvent)
{
	pCloseEvent->ignore();
}

#include "moc_smeviewwindow.cpp"