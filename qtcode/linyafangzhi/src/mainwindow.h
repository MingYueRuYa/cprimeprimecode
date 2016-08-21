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

protected slots:
    void DoComDyeWorkChanged(const QString &pDyeWorkName);

    void DoComClientNameChanged(const QString &pClientName);

    void DoComSpecficationProductsChanged(const QString &pSepificationProducts);

	void DoOrderInfoSearched();

    void DoImport();

	void DoTableCellClicked(const int &pRow, const int &pColumn);

private:
	SearchDockWidget *mSearchDockWidget;

	QWidget *mSearchDockWidgetContents;

	QVBoxLayout *mDockVLayout;

private:
    OrderInfoList mOrderInfoList;

    QSet<QString> mDyeWorkSet;

    QSet<QString> mClientNameSet;

    QSet <QString> mSpecificationProducetSet;

};

#endif // mainwindow_h
