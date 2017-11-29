/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef smeaddtimerdialog_h

#define smeaddtimerdialog_h

#include <QtWidgets/QDialog>

#include "ui_smeaddtimerdialog.h"

class smeAddTimerDialog : public QDialog, public Ui::AddTimerDialog
{
	Q_OBJECT

public:
	smeAddTimerDialog(QWidget *pParent = 0);

	~smeAddTimerDialog();

protected slots:
	void DoOK();

	void DoCancel();

	void DoPositionUpdated(const int &pXPosition, const int &pYPosition);

signals:
	void OnTimerAdded();

};

#endif //smeaddtimerdialog_h