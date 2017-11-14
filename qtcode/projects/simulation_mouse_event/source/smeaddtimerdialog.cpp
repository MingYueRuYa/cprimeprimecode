/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include "smeaddtimerdialog.h"

smeAddTimerDialog::smeAddTimerDialog(QWidget *pParent /* = 0 */)
: QDialog(pParent)
{
	setupUi(this);

	connect(btn_ok, SIGNAL(clicked()), this, SLOT(DoOK()));
	connect(btn_cancel, SIGNAL(clicked()), this, SLOT(DoCancel()));
}

smeAddTimerDialog::~smeAddTimerDialog()
{
}

void smeAddTimerDialog::DoOK()
{
	emit OnTimerAdded();
	accept();
}

void smeAddTimerDialog::DoCancel()
{
	reject();
}

void smeAddTimerDialog::DoPositionUpdated(const int &pXPosition, const int &pYPosition)
{
	edt_startposition->setText(QString::number(pXPosition));
	edt_endposition->setText(QString::number(pYPosition));
}

#include "moc_smeaddtimerdialog.cpp"

