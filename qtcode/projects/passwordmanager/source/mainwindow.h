/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QTableWidgetItem>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QShortcut>

#include "tablewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *pParent = 0);

    ~MainWindow();
private:
    void Init();

    void CreateAction();

    bool LoadInfo();

    void WriteSettings();

    void ReadSettings();

protected:
    void closeEvent(QCloseEvent *pEvent);

protected slots:
    void DoInsert();

    bool DoSave();

    void DoTableItemChanged(QTableWidgetItem *pItem);

private:
     QVBoxLayout *mVBoxlayout;

     TableWidget *mTableWidget;

     QWidget *mCentralWidget;

     QMenu *mMenu;

     QAction *mInsertAction;

     QAction *mSaveAction;

     bool mRegisterFlag;

     bool mIsModified;

     QPoint mPositionPoint;

     QPoint mWindowSize;

     /*!
       ctrl + s 保存
     */
     QShortcut *mSaveShrotcut;

     /*!
       ctrl + i 插入
     */
     QShortcut *mInsertShrotcut;
};

#endif // MAINWINDOW_H
