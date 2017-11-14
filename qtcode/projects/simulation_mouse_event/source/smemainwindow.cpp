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
	CreateMenu();
	mCurrentEventType = Position;

	connect(btn_start, SIGNAL(clicked()), this, SLOT(DoStart()));
	connect(btn_stop, SIGNAL(clicked()), this, SLOT(DoStop()));
	connect(btn_getposition, SIGNAL(clicked()), this, SLOT(DoGetPosition()));
	connect(&mViewWindow, SIGNAL(OnUpdatePosition(int, int)), this, SLOT(DoPositionUpdated(int ,int)));
	connect(tablewidget_timerinfo, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(DoShowMenu(QPoint)));
	mViewWindow.show();
}

smeMainWindow::~smeMainWindow()
{
	ClearTimerInfo();
}

void smeMainWindow::closeEvent(QCloseEvent *pCloseEvent)
{
	qApp->exit();
}

void smeMainWindow::UpdateUi()
{
	this->edt_xposition->setPlaceholderText(tr("X Postion"));
	this->edt_yposition->setPlaceholderText(tr("Y Postion"));
	this->tablewidget_timerinfo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	connect(this, SIGNAL(OnPositionUpdated(int, int)), &mDialog, SLOT(DoPositionUpdated(int, int)));
	connect(&mDialog, SIGNAL(OnTimerAdded()), this, SLOT(DoTimerAdded()));
}

void smeMainWindow::CreateMenu()
{
	mMenu = new QMenu(this);

	QAction *addaction = new QAction(tr("Add"), this);
	connect(addaction, SIGNAL(triggered()), this, SLOT(DoAddTimer()));
	mMenu->addAction(addaction);

	QAction *deleteaction = new QAction(tr("Delete"), this);
	connect(deleteaction, SIGNAL(triggered()), this, SLOT(DoDeleteTimer()));
	mMenu->addAction(deleteaction);

	QAction *clearaction = new QAction(tr("Clear"), this);
	connect(clearaction, SIGNAL(triggered()), this, SLOT(DoClearTimer()));
	mMenu->addAction(clearaction);
}

void smeMainWindow::ClearTimerInfo()
{
	foreach (smeTimeInfo *timeinfo, mTimeInfoList) {
		delete timeinfo;
		timeinfo = NULL;
	}
	mTimeInfoList.clear();
}

void smeMainWindow::DoStart()
{
	mCurrentEventType = Start;

	foreach (smeTimeInfo *timeinfo, mTimeInfoList) {
		timeinfo->StartTimer();
	}
}

void smeMainWindow::DoStop()
{
	mCurrentEventType = Stop;
	foreach (smeTimeInfo *timeinfo, mTimeInfoList) {
		timeinfo->StopTimer();
	}
}

void smeMainWindow::DoGetPosition()
{
	mCurrentEventType = Position;
}

void smeMainWindow::DoPositionUpdated(const int &pXPosition, const int &pYPosition)
{
	edt_xposition->setText(QString::number(pXPosition));
	edt_yposition->setText(QString::number(pYPosition));

	emit OnPositionUpdated(pXPosition, pYPosition);

	if (Position != mCurrentEventType) {
		return;
	}
	//更新table中的内容
	int currentrow = tablewidget_timerinfo->currentRow();
	if (currentrow < 0) {
		return;
	}
	tablewidget_timerinfo->item(currentrow, 3)->setText(QString::number(pXPosition));
	tablewidget_timerinfo->item(currentrow, 4)->setText(QString::number(pYPosition));
}

void smeMainWindow::DoAddTimer()
{
	mDialog.show();
}

void smeMainWindow::DoTimerAdded()
{
	smeTimeInfo *timeinfo = new smeTimeInfo();
	timeinfo->SetTime(QTime::fromString(mDialog.edt_time->text(), "hh:mm:ss"));
	timeinfo->SetInterval(mDialog.edt_interval->text().toInt());
	timeinfo->SetStartPosition(mDialog.edt_startposition->text().toInt());
	timeinfo->SetEndPosition(mDialog.edt_endposition->text().toInt());
	timeinfo->SetCount(mDialog.edt_count->text().toInt());
	connect(timeinfo, SIGNAL(OnMouseClickEvent(int, int)), this, SLOT(DoMouseClickEvent(int, int)));
	mTimeInfoList.append(timeinfo);
	int rowcount = tablewidget_timerinfo->rowCount();
	tablewidget_timerinfo->insertRow(rowcount);
	tablewidget_timerinfo->setItem(rowcount, 0, 
		new QTableWidgetItem(QString::number(rowcount + 1)));
	tablewidget_timerinfo->setItem(rowcount, 1, 
		new QTableWidgetItem(timeinfo->GetTime().toString("hh:mm:ss")));
	tablewidget_timerinfo->setItem(rowcount, 2, 
		new QTableWidgetItem(QString::number(timeinfo->GetInterval())));
	tablewidget_timerinfo->setItem(rowcount, 3, 
		new QTableWidgetItem(QString::number(timeinfo->GetStartPositoin())));
	tablewidget_timerinfo->setItem(rowcount, 4, 
		new QTableWidgetItem(QString::number(timeinfo->GetEndPositoin())));
	tablewidget_timerinfo->setItem(rowcount, 5, 
		new QTableWidgetItem(QString::number(timeinfo->GetCount())));
}

void smeMainWindow::DoDeleteTimer()
{
	if (tablewidget_timerinfo->rowCount() <= 0) {
		return;
	}
	tablewidget_timerinfo->removeRow(tablewidget_timerinfo->currentRow());
}

void smeMainWindow::DoClearTimer()
{
	while (tablewidget_timerinfo->rowCount() > 0) {
		tablewidget_timerinfo->removeRow(0);
	}
}

void smeMainWindow::DoSaveTimer()
{
	foreach (smeTimeInfo *timeinfo, mTimeInfoList) {
		if (! timeinfo->SaveToXml()) {
			continue;
		}
	}
}

void smeMainWindow::DoShowMenu(const QPoint &pPoint)
{
	mMenu->exec(QCursor::pos());
}

void smeMainWindow::DoMouseClickEvent(const int &mStartPositoin, const int &mEndPosition)
{
	//设置光标位置
	SetCursorPos(mStartPositoin, mEndPosition);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//鼠标点下
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//鼠标松开
	listwidget_loginfo->addItem(new QListWidgetItem(QString::number(listwidget_loginfo->count()) + " - "
		+ QString::number(mStartPositoin) + ", " + QString::number(mEndPosition) + " " + 
		QTime::currentTime().toString("hh:mm:ss")));
}

#include "moc_smemainwindow.cpp"