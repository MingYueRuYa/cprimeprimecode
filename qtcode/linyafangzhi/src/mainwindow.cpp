/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtGui/QMessageBox>

#include "dbpack.h"
#include "mainwindow.h"

const QString ALL = tr("ALL");

const int G_COLUMN_COUNT = 6;

MainWindow::MainWindow(QWidget *pParent) : QMainWindow(pParent)
{
    setupUi(this);
    CreateSample();
    UpdateUi();

    connect(combo_dyework, SIGNAL(currentIndexChanged(const QString &)),this,
            SLOT(DoComDyeWorkChanged(const QString &)));
    connect(combo_clientname, SIGNAL(currentIndexChanged(const QString &)),this,
            SLOT(DoComClientNameChanged(const QString &)));
    connect(combo_specificationproducts, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(DoComSpecficationProductsChanged(const QString &)));

    connect(btn_import, SIGNAL(clicked()), this, SLOT(DoImport()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    QHeaderView *headerview = tableWidget->horizontalHeader();
    headerview->resizeSection(0, width() * 0.10);
    headerview->resizeSection(1, width() * 0.25);
    headerview->resizeSection(2, width() * 0.25);
    headerview->resizeSection(3, width() * 0.10);
    headerview->resizeSection(4, width() * 0.10);
    headerview->resizeSection(5, width() * 0.10);
}

void MainWindow::UpdateUi()
{
    if (mOrderInfoList.count() < 0) {
        return;
    }

    foreach (OrderInfo info, mOrderInfoList) {
        if (! info.GetDyeWork().isEmpty()) {
            mDyeWorkSet.insert(info.GetDyeWork());
        }
        if (! info.GetClientName().isEmpty()) {
            mClientNameSet.insert(info.GetClientName());
        }
        if (! info.GetSpecificationProduct().isEmpty()) {
            mSpecificationProducetSet.insert(info.GetSpecificationProduct());
        }
    }

    QSet<QString>::iterator ibegin = mDyeWorkSet.begin();
    while (ibegin != mDyeWorkSet.end()) {
        combo_dyework->addItem(*ibegin);
        ++ibegin;
    }
	combo_dyework->addItem(ALL);

    ibegin = mClientNameSet.begin();
    while (ibegin != mClientNameSet.end()) {
        combo_clientname->addItem(*ibegin);
        ++ibegin;
    }
	combo_clientname->addItem(ALL);

    ibegin = mSpecificationProducetSet.begin();
    while (ibegin != mSpecificationProducetSet.end()) {
        combo_specificationproducts->addItem(*ibegin);
        ++ibegin;
    }
	combo_specificationproducts->addItem(ALL);

    QTableWidgetItem *widgetitem = NULL;
    for (int i = 0; i < mOrderInfoList.count(); ++i) {
        int rowcount = tableWidget->rowCount();
        tableWidget->insertRow(rowcount);
        widgetitem = new QTableWidgetItem(mOrderInfoList[i].GetDyeWork());
        widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tableWidget->setItem(rowcount, 0, widgetitem);

        widgetitem = new QTableWidgetItem(mOrderInfoList[i].GetOrderDate());
        widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tableWidget->setItem(rowcount, 1, widgetitem);

        widgetitem = new QTableWidgetItem(mOrderInfoList[i].GetClientName());
        widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tableWidget->setItem(rowcount, 2, widgetitem);

        widgetitem = new QTableWidgetItem(mOrderInfoList[i].GetClientContact());
        widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tableWidget->setItem(rowcount, 3, widgetitem);

        widgetitem = new QTableWidgetItem(mOrderInfoList[i].GetSpecificationProduct());
        widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tableWidget->setItem(rowcount, 4, widgetitem);

        widgetitem = new QTableWidgetItem(mOrderInfoList[i].GetColor());
        widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        tableWidget->setItem(rowcount, 5, widgetitem);
    }
}

bool MainWindow::CreateSample()
{
#ifdef Q_OS_WIN32
    QTextCodec *codec = QTextCodec::codecForName("GBK");
#endif
#ifdef Q_OS_LINUX
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
#endif
    QFile file("order.txt");
    if (! file.open(QIODevice::ReadOnly)) {
        file.close();
		QMessageBox::information(NULL, APPLICATION_NAME, file.errorString());
        return false;
    }
    while (! file.atEnd()) {
        OrderInfo orderinfo;
        QByteArray line = file.readLine();
        QStringList stringlist = codec->toUnicode(line).split(",");
		if (stringlist.count() < 6) {
			continue;
		}
        orderinfo.SetDyeWork(stringlist[0].trimmed());
        orderinfo.SetOrderDate(stringlist[1]);
        orderinfo.SetClientName(stringlist[2]);
        orderinfo.SetClientContact(stringlist[3]);
        orderinfo.SetSpecificationProduct(stringlist[4].trimmed());
        orderinfo.SetColor(stringlist[5].trimmed());
        //orderinfo.SetMenFu(stringlist[6].trimmed());
        //orderinfo.SetCount(stringlist[7].toInt());
        //orderinfo.SetPrice(stringlist[8].toDouble());
        //orderinfo.SetProcessCost(stringlist[9].toDouble());
        //orderinfo.SetIsShangRou(stringlist[10] == "1" ? true : false);
        //orderinfo.SetOtherCraftwork(stringlist[11]);
        //orderinfo.SetColorTextilePrintPrice(stringlist[12].toDouble());
        //orderinfo.SetGradeACount(stringlist[13].toInt());
        //orderinfo.SetGradeBCount(stringlist[14].toInt());
        //orderinfo.SetGreyClothSupplier(stringlist[15]);
        //orderinfo.SetGreyClothCount(stringlist[16].toInt());
        //orderinfo.SetGreyClothPrice(stringlist[17].toDouble());
        //orderinfo.SetMemory(stringlist[18].trimmed());
        mOrderInfoList.append(orderinfo);
    }
    return true;
}

void MainWindow::SerachInfo(const SearchType &pSearchType, const QString &pSerachText)
{
    int count = 0;
    if (pSearchType == DyeWork) {
        foreach (OrderInfo info, mOrderInfoList) {
            if (info.GetDyeWork() == pSerachText) {
                ++count;
            }
        }
    }
    else if (pSearchType == ClientName) {
        foreach (OrderInfo info, mOrderInfoList) {
            if (info.GetClientName() == pSerachText) {
                ++count;
            }
        }
    }
    else if (pSearchType == SpecificationProducts) {
        foreach (OrderInfo info, mOrderInfoList) {
            if (info.GetSpecificationProduct() == pSerachText) {
                ++count;
            }
        }
    }
    else {
        return;
    }

    int j = 0;
    foreach (OrderInfo info, mOrderInfoList) {
        if (pSearchType == DyeWork) {
            if (info.GetDyeWork() != pSerachText) {
                continue;
            }
        }
        else if (pSearchType == ClientName) {
            if (info.GetClientName() != pSerachText) {
                continue;
            }
        }
        else if (pSearchType == SpecificationProducts) {
            if (info.GetSpecificationProduct() != pSerachText) {
                continue;
            }
        }
        else {
            continue;
        }
        if (count > tableWidget->rowCount()) {
            int rowcount = tableWidget->rowCount();
            while ((count - rowcount) > 0) {
                tableWidget->insertRow(rowcount);
                for (int i = 0; i < G_COLUMN_COUNT; ++i) {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
                    tableWidget->setItem(rowcount, i, item);
                }
                rowcount = tableWidget->rowCount();
            }
        }
        tableWidget->item(j, 0)->setText(info.GetDyeWork());
        tableWidget->item(j, 1)->setText(info.GetOrderDate());
        tableWidget->item(j, 2)->setText(info.GetClientName());
        tableWidget->item(j, 3)->setText(info.GetClientContact());
        tableWidget->item(j, 4)->setText(info.GetSpecificationProduct());
        tableWidget->item(j, 5)->setText(info.GetColor());
        ++j;
    }
    while (count < tableWidget->rowCount()) {
        tableWidget->removeRow(tableWidget->rowCount() - 1);
    }
}

void MainWindow::DoComDyeWorkChanged(const QString &pDyeWorkName)
{
    SerachInfo(DyeWork, pDyeWorkName);
}

void MainWindow::DoComClientNameChanged(const QString &pClientName)
{
	SerachInfo(ClientName, pClientName);
}

void MainWindow::DoComSpecficationProductsChanged(const QString &pSepificationProducts)
{
      SerachInfo(SpecificationProducts, pSepificationProducts);
}

void MainWindow::DoImport()
{

}

#include "moc_mainwindow.cpp"
