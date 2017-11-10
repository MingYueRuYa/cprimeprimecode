/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef smemainwindow_h
#define smemainwindow_h

#include<Windows.h>

#include <QtGui/QMainWindow>
#include <QtGui/QMouseEvent>
#include <QtGui/QMenu>
#include <QtGui/QAction>

#include "ui_smemainwindow.h"
#include "smeviewwindow.h"
#include "smetimeinfo.h"
#include "smeaddtimerdialog.h"

/*! \brief smeMainWindow
    \author liushixiong (635672377@qq.com)
    \version 0.01
    \date 20016.09.01

    smeMainWindow Ö÷´°¿Ú
*/
class smeMainWindow : public QMainWindow, public Ui::smeMainWindow
{
	Q_OBJECT

public:
	typedef enum {None, Start, Stop, Position} EventType;

public:
	smeMainWindow(QWidget *pParent = 0);

	~smeMainWindow();

protected:
	void closeEvent(QCloseEvent *pCloseEvent);

	void UpdateUi();

	void CreateMenu();

	void ClearTimerInfo();

	void LoadTimersInfo();

protected slots:
	void DoStart();

	void DoStop();

	void DoGetPosition();

	void DoPositionUpdated(const int &pXPosition, const int &pYPosition);

	void DoAddTimer();

	void DoTimerAdded();

	void DoDeleteTimer();

	void DoClearTimer();

	void DoSaveTimer();

	void DoShowMenu(const QPoint &pPoint);

	void DoMouseClickEvent(const int &mStartPositoin, const int &mEndPosition);

signals:
	void OnPositionUpdated(const int &pXPosition, const int &pYPosition);

private:
	smeAddTimerDialog mDialog;

	smeViewWindow mViewWindow;

private:
	EventType mCurrentEventType;

	QMenu *mMenu;

	QList<smeTimeInfo *> mTimeInfoList;

};

#endif //smemainwindow_h