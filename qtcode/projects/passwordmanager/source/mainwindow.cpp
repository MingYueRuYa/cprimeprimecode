/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QSettings>
#include <QtGui/QMenuBar>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>
//#include <QtCrypto>

#include "config.h"
#include "mainwindow.h"

//TODO 根据逗号进行分割的时候会有问题，如果用户的密码含有逗号，这样解析就是错误的  ---> 对密码进行加密处理，就不存在逗号问题 ---> 加密算法选取
//TODO 如果光标，没有离开单元格的时候，在保存的程序异常退出--->解决，因为QTableWidgetItem可能为空
//TODO 每次都把原来的野保存了一份，冗余保存 ---> 暂时没有方案
//TODO 添加网络功能，上传文件到服务器中 --->服务器还没有搭建

MainWindow::MainWindow(QWidget *pParent)
    : QMainWindow(pParent)//, mCryptographicHash(QCryptographicHash::Sha1)
{
    //QCA::Initializer init;
    mRegisterFlag = false;
    mIsModified = false;

    //读取配置文件，如果mRegisterFlag = false, 表示是第一次使用
    ReadSettings();
    SetupUi();

    mBaseEncrypt = EncryptController::__Instance()->GetBaseEncrypt("simplecrypt");
    Load();
    setWindowModified(true);
    setWindowTitle(APPLICATION_NAME);

    connect(mTableWidget, SIGNAL(itemChanged(QTableWidgetItem *)), this,
            SLOT(DoTableItemChanged(QTableWidgetItem *)));
}

MainWindow::~MainWindow()
{
    if (NULL != mBaseEncrypt) {
        delete mBaseEncrypt;
        mBaseEncrypt = NULL;
    }
}

void MainWindow::SetupUi()
{
    mInsertShrotcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), this);
    connect(mInsertShrotcut, SIGNAL(activated()), this, SLOT(DoInsert()));

    mDeleteShrotcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(mDeleteShrotcut, SIGNAL(activated()), this, SLOT(DoDelete()));

    mAllDeleteShrotcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Delete), this);
    connect(mAllDeleteShrotcut, SIGNAL(activated()), this, SLOT(DoAllDelete()));

    mSaveShrotcut = new QShortcut(QKeySequence::Save, this);
    connect(mSaveShrotcut, SIGNAL(activated()), this ,SLOT(DoSave()));

    QDesktopWidget *desktopwidget = QApplication::desktop();
    int deskwidth = desktopwidget->width();
    int deskheight = desktopwidget->height();

    mCentralWidget = new QWidget(this);
    mVBoxlayout = new QVBoxLayout(mCentralWidget);
    mTableWidget = new TableWidget(mCentralWidget);

    mVBoxlayout->addWidget(mTableWidget);
    setCentralWidget(mCentralWidget);

    CreateAction();
    //居中显示
    if (! mRegisterFlag) {
        setGeometry((deskwidth - 800) / 2, (deskheight - 600) / 2, 800, 600);
    }
    else {
        setGeometry(mPositionPoint.x(), mPositionPoint.y(), mWindowSize.x(), mWindowSize.y());
    }
}

void MainWindow::CreateAction()
{
    mInsertAction = new QAction(tr("insert"), this);
    connect(mInsertAction, SIGNAL(triggered()), this, SLOT(DoInsert()));

    mDeleteAction = new QAction(tr("delete"), this);
    connect(mDeleteAction, SIGNAL(triggered()), this, SLOT(DoDelete()));

    mAllDeleteAction = new QAction(tr("delete all"), this);
    connect(mAllDeleteAction, SIGNAL(triggered()), this, SLOT(DoAllDelete()));

    mSaveAction = new QAction(tr("save"), this);
    connect(mSaveAction, SIGNAL(triggered()), this, SLOT(DoSave()));

    mMenu = menuBar()->addMenu(tr("operation"));
    mMenu->addAction(mInsertAction);
    mMenu->addAction(mDeleteAction);
    mMenu->addAction(mAllDeleteAction);
    mMenu->addAction(mSaveAction);
}

bool MainWindow::Load()
{
    QFile file(PASSWORD_NAME);
    if (! file.exists()) {
        if (mRegisterFlag) {
            QMessageBox::information(this, tr("info"),tr("Not find password file."));
        }
        return false;
    }
    if (! file.open(QFile::ReadOnly)) {
        QMessageBox::information(this, tr("info"), tr("Open file failed."));
        return false;
    }
    QTextStream textstream(&file);
    QString linestring = 0;
    while (1) {
        linestring = textstream.readLine();
        if (linestring.isEmpty()) {
            break;
        }
        QStringList strlist = linestring.split(",");
        mTableWidget->insertRow(mTableWidget->rowCount());
        for (int i = 0; i < strlist.count(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if (i == strlist.count() - 1) {
                item->setText("");
                if (NULL != mBaseEncrypt) {
                    item->setText(mBaseEncrypt->Decrypt(strlist[i]));
                }
            } else {
                item->setText(strlist[i]);
            }
            mTableWidget->setItem(mTableWidget->rowCount() - 1, i, item);
        }
    }
    return true;
}

void MainWindow::WriteSettings()
{
    QSettings settings("passwordmanager");
    settings.setValue("flag/registerflag", "true");
    settings.setValue("position/pos", this->pos());
    settings.setValue("info/size/height", this->height());
    settings.setValue("info/size/width", this->width());
}

void MainWindow::ReadSettings()
{
    QSettings settings("passwordmanager");
    mRegisterFlag = settings.value("flag/registerflag", "false").toBool();
    mPositionPoint = settings.value("position/pos", QPoint(0, 0)).value<QPoint>();
    mWindowSize.setX(settings.value("info/size/width", 800).toInt());
    mWindowSize.setY(settings.value("info/size/height", 600).toInt());
}

void MainWindow::closeEvent(QCloseEvent *pEvent)
{
    if (mIsModified) {
        QMessageBox::StandardButton standardbutton = QMessageBox::information(this,
                 APPLICATION_NAME, tr("Are you sure to close window?"),
                 QMessageBox::Yes | QMessageBox::No | QMessageBox::SaveAll, QMessageBox::No);
        if (QMessageBox::SaveAll == standardbutton) {
            DoSave();
            //WriteSettings();
        } else if (QMessageBox::No == standardbutton) {
            pEvent->ignore();
            return;
        } else {
            //TODO if standardbutton is yes, todo nothing.
        }
    }
    WriteSettings();
}

void MainWindow::DoInsert()
{
    mTableWidget->insertRow(mTableWidget->rowCount());
}

void MainWindow::DoDelete()
{
    int currentrow = mTableWidget->currentRow();
    if (-1 == currentrow){
        return;
    }
    mTableWidget->removeRow(currentrow);
    mIsModified = true;
    setWindowTitle(QString(APPLICATION_NAME) + "[*]");
}

void MainWindow::DoAllDelete()
{
    int rowcount = mTableWidget->rowCount();
    for (int i = 0; i < rowcount; ++i) {
        mTableWidget->removeRow(0);
    }
    mIsModified = true;
    setWindowTitle(QString(APPLICATION_NAME) + "[*]");
}

bool MainWindow::DoSave()
{
    QFile file(PASSWORD_NAME);
    if (! file.open(QFile::WriteOnly)) {
        file.close();
        return false;
    }
    QTextStream textstream(&file);

    for (int i = 0; i < mTableWidget->rowCount(); ++i) {
        if (NULL == mTableWidget->item(i, 0) || NULL == mTableWidget->item(i, 1) || NULL == mTableWidget->item(i, 2)) {
            QMessageBox::information(this, tr("info"), tr("Please save modify information, Press enter."));
            return false;
        }
        if (NULL == mBaseEncrypt) {
            return false;
        }
        QString passwordencryptstr = mBaseEncrypt->Encrypt(mTableWidget->item(i, 2)->text());
        textstream << mTableWidget->item(i, 0)->text() << "," << mTableWidget->item(i, 1)->text() << "," << passwordencryptstr;
        textstream << "\n";
    }
    file.close();
    WriteSettings();
    mIsModified = false;
    setWindowTitle(APPLICATION_NAME);
    return true;
}

void MainWindow::DoTableItemChanged(QTableWidgetItem *)
{
    setWindowTitle(APPLICATION_NAME + QString("[*]"));
    mIsModified = true;
}
