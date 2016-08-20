/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef searchdockwidget_h

#define searchdockwidget_h

#include <QtGui/QDockWidget>

#include "ui_searchdockwidget.h"
#include "dbpack.h"

class SearchDockWidget : public QDockWidget, protected Ui::SearchDockWidget
{
	Q_OBJECT

public:
	SearchDockWidget(const OrderInfoList &pOrderInfoList, QWidget *pParent = 0);

	~SearchDockWidget();

	OrderInfoList FilterOrderInfo();

protected:
	void paintEvent(QPaintEvent *event);

	void resizeEvent(QResizeEvent *);

	void UpdateUi();

signals:
	void OnOrderInfoSearched();

protected slots:
	void DoComDyeWorkChanged(const QString &pDyeWorkName);

	void DoComClientNameChanged(const QString &pClientName);

	void DoComSpecficationProductsChanged(const QString &pSepificationProducts);

	void DoSearch();

private:
	OrderInfoList mOrderInfoList;

};

#endif //searchdockwidget_h