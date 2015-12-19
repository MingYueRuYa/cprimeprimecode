/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef mainwindow_h
#define mainwindow_h

#include <QMenu>
#include <QAction>
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QShortcut>
#include <QtCore/QCryptographicHash>

#include "tablewidget.h"
#include "encryptpack.h"

/**
  * @brief   main window
  * @author  liushixiong (635672377@qq.com)
  * @version 0.01
  * @date    2015/11/30
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *pParent = 0);

    ~MainWindow();

private:
    void SetupUi();

    void CreateAction();

    bool Load();

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
      * ctrl + s 保存
      */
     QShortcut *mSaveShrotcut;

     /*!
      * ctrl + i 插入
      */
     QShortcut *mInsertShrotcut;

     BaseEncrypt *mBaseEncrypt;

     //QCryptographicHash mCryptographicHash;
};

#endif // mainwindow_h
