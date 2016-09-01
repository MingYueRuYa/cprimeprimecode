/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include "smemainwindow.h"

smeMainWindow::smeMainWindow(QWidget *pParent)
: QMainWindow(pParent)
{
	setupUi(this);
	UpdateUi();
}

smeMainWindow::~smeMainWindow()
{

}

void smeMainWindow::UpdateUi()
{
	this->edt_xposition->setPlaceholderText(tr("X Postion"));
	this->edt_yposition->setPlaceholderText(tr("Y Postion"));
	this->tablewidget_timerinfo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

#include "moc_smemainwindow.cpp"