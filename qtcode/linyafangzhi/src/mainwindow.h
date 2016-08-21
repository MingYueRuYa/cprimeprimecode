/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef mainwindow_h
#define mainwindow_h

#include <QtCore/QTextCodec>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>

#include "ui_mainwindow.h"
#include "dbpack.h"
#include "searchdockwidget.h"
#include "quickguidewidget.h"

class MainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT

public:
    typedef enum {DyeWork, ClientName, SpecificationProducts, ALL} SearchType;

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent *);

    void UpdateUi();

    bool CreateSample();

    void SerachInfo(const SearchType &pSearchType, const QString &pSerachText);

	void InsertDataToTable(const OrderInfoList &pOrderInfoList);

	void CreateAction();

protected slots:
    void DoComDyeWorkChanged(const QString &pDyeWorkName);

    void DoComClientNameChanged(const QString &pClientName);

    void DoComSpecficationProductsChanged(const QString &pSepificationProducts);

	void DoOrderInfoSearched();

    void DoImport();

	void DoTableCellClicked(const int &pRow, const int &pColumn);

	//action槽函数
protected slots:
	void DoExit();

	void DoQuickGuide();

private:
	SearchDockWidget *mSearchDockWidget;

	QWidget *mSearchDockWidgetContents;

	QVBoxLayout *mDockVLayout;

	QuickGuideWidget *mQuickGuideWidget;

private:
    OrderInfoList mOrderInfoList;

    QSet<QString> mDyeWorkSet;

    QSet<QString> mClientNameSet;

    QSet <QString> mSpecificationProducetSet;

public:
	/*!
		让 QuickGuideWidget 成为 MainWindow 的友元，使得它能访问所有的子窗口以获取他们的位置。
	*/
	friend class QuickGuideWidget;

};

#endif // mainwindow_h
