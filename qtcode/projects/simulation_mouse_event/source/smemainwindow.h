/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef smemainwindow_h
#define smemainwindow_h

#include <QtGui/QMainWindow>

#include "ui_smemainwindow.h"

class smeMainWindow : public QMainWindow, public Ui::smeMainWindow
{
	Q_OBJECT

public:
	smeMainWindow(QWidget *pParent = 0);

	~smeMainWindow();

protected:
	void UpdateUi();

};

#endif //smemainwindow_h