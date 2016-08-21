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

const QString G_ALL = ("ALL");
const int G_COLUMN_COUNT = 7;

MainWindow::MainWindow(QWidget *pParent) : QMainWindow(pParent)
{
	setProperty("Form", true);
    setupUi(this);
    CreateSample();
    UpdateUi();
	//设置窗体标题栏隐藏
	//this->setWindowFlags(Qt::FramelessWindowHint |
	//	Qt::WindowSystemMenuHint |
	//	Qt::WindowMinMaxButtonsHint);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *)
{
}

void MainWindow::UpdateUi()
{
	
	mSearchDockWidget = new SearchDockWidget(mOrderInfoList, this);
	mSearchDockWidget->setMinimumWidth(width() * 0.25);
	this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), mSearchDockWidget);
	connect(mSearchDockWidget, SIGNAL(OnOrderInfoSearched()), this, SLOT(DoOrderInfoSearched()));

	tableWidget->horizontalHeader()->setStretchLastSection(true);
	connect(tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(DoTableCellClicked(int, int)));

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
	InsertDataToTable(mOrderInfoList);
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
	int id = 1;
    while (! file.atEnd()) {
        OrderInfo orderinfo;
        QByteArray line = file.readLine();
        QStringList stringlist = codec->toUnicode(line).split(",");
		if (stringlist.count() < 19) {
			continue;
		}
		orderinfo.SetOrderId(id++);
        orderinfo.SetDyeWork(stringlist[0].trimmed());
        orderinfo.SetOrderDate(stringlist[1]);
        orderinfo.SetClientName(stringlist[2]);
        orderinfo.SetClientContact(stringlist[3]);
        orderinfo.SetSpecificationProduct(stringlist[4].trimmed());
        orderinfo.SetColor(stringlist[5].trimmed());
        orderinfo.SetMenFu(stringlist[6].trimmed());
        orderinfo.SetCount(stringlist[7].toInt());
        orderinfo.SetPrice(stringlist[8].toDouble());
        orderinfo.SetProcessCost(stringlist[9].toDouble());
        orderinfo.SetIsShangRou(stringlist[10] == "1" ? true : false);
        orderinfo.SetOtherCraftwork(stringlist[11]);
        orderinfo.SetColorTextilePrintPrice(stringlist[12].toDouble());
        orderinfo.SetGradeACount(stringlist[13].toInt());
        orderinfo.SetGradeBCount(stringlist[14].toInt());
        orderinfo.SetGreyClothSupplier(stringlist[15]);
        orderinfo.SetGreyClothCount(stringlist[16].toInt());
        orderinfo.SetGreyClothPrice(stringlist[17].toDouble());
        orderinfo.SetMemory(stringlist[18].trimmed());
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
    else if (pSearchType == ALL) {
        foreach (OrderInfo info, mOrderInfoList) {
            ++count;
        }
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
        else if (pSearchType == ALL) {
            //TODO todnothing
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
        tableWidget->item(j, 0)->setText(QString::number(j + 1));
        if (pSearchType == DyeWork) {
            tableWidget->item(j, 1)->setBackgroundColor(QColor(39, 169, 255, 255));
        }
        else {
            tableWidget->item(j, 1)->setBackgroundColor(Qt::white);
        }
        tableWidget->item(j, 1)->setText(info.GetDyeWork());
        tableWidget->item(j, 2)->setText(info.GetOrderDate());
        tableWidget->item(j, 3)->setText(info.GetClientName());
        if (pSearchType == ClientName) {
            tableWidget->item(j, 3)->setBackgroundColor(Qt::red);
        }
        else {
            tableWidget->item(j, 3)->setBackgroundColor(Qt::white);
        }
        tableWidget->item(j, 4)->setText(info.GetClientContact());
        tableWidget->item(j, 5)->setText(info.GetSpecificationProduct());
        if (pSearchType == SpecificationProducts) {
            tableWidget->item(j, 5)->setBackgroundColor(QColor(0, 170, 0, 255));
        }
        else {
            tableWidget->item(j, 5)->setBackgroundColor(Qt::white);
        }
        tableWidget->item(j, 6)->setText(info.GetColor());
        ++j;
    }
    while (count < tableWidget->rowCount()) {
        tableWidget->removeRow(tableWidget->rowCount() - 1);
    }
}

void MainWindow::InsertDataToTable(const OrderInfoList &pOrderInfoList)
{
	while (tableWidget->rowCount() > 0) {
		tableWidget->removeRow(0);
	}
	QTableWidgetItem *widgetitem = NULL;
	for (int i = 0; i < pOrderInfoList.count(); ++i) {
		OrderInfo orderinfo = pOrderInfoList[i];
		int rowcount = tableWidget->rowCount();
		tableWidget->insertRow(rowcount);
		widgetitem = new QTableWidgetItem(QString::number(i + 1));
		widgetitem->setData(Qt::UserRole, orderinfo.GetOrderId());
		widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		tableWidget->setItem(rowcount, 0, widgetitem);

		widgetitem = new QTableWidgetItem(orderinfo.GetDyeWork());
		widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		tableWidget->setItem(rowcount, 1, widgetitem);

		widgetitem = new QTableWidgetItem(orderinfo.GetOrderDate());
		widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		tableWidget->setItem(rowcount, 2, widgetitem);

		widgetitem = new QTableWidgetItem(orderinfo.GetClientName());
		widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		tableWidget->setItem(rowcount, 3, widgetitem);

		widgetitem = new QTableWidgetItem(orderinfo.GetClientContact());
		widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		tableWidget->setItem(rowcount, 4, widgetitem);

		widgetitem = new QTableWidgetItem(orderinfo.GetSpecificationProduct());
		widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		tableWidget->setItem(rowcount, 5, widgetitem);

		widgetitem = new QTableWidgetItem(orderinfo.GetColor());
		widgetitem->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		tableWidget->setItem(rowcount, 6, widgetitem);
	}
}

void MainWindow::DoComDyeWorkChanged(const QString &pDyeWorkName)
{
    if (G_ALL == pDyeWorkName) {
        SerachInfo(ALL, "");
    }
    else {
        SerachInfo(DyeWork, pDyeWorkName);
    }
}

void MainWindow::DoComClientNameChanged(const QString &pClientName)
{
    if (G_ALL == pClientName) {
        SerachInfo(ALL, "");
    }
    else {
        SerachInfo(ClientName, pClientName);
    }
}

void MainWindow::DoComSpecficationProductsChanged(const QString &pSepificationProducts)
{
    if (G_ALL == pSepificationProducts) {
        SerachInfo(ALL, "");
    }
    else {
      SerachInfo(SpecificationProducts, pSepificationProducts);
    }
}

void MainWindow::DoOrderInfoSearched()
{
	OrderInfoList temporderinfolist = mSearchDockWidget->FilterOrderInfo();
	InsertDataToTable(temporderinfolist);
}

void MainWindow::DoImport()
{

}

void MainWindow::DoTableCellClicked(const int &pRow, const int &pColumn)
{
	if (pRow < 0 || pRow > tableWidget->rowCount()) {
		return;
	}
	int orderid = tableWidget->item(pRow, 0)->data(Qt::UserRole).toInt();
	OrderInfo orderinfo;
	foreach (OrderInfo info, mOrderInfoList) {
		if (info.GetOrderId() != orderid) {
			continue;
		}
		orderinfo = info;
		break;
	}
	edt_clientcount->setText(QString::number(orderinfo.GetCount()));
	edt_price->setText(QString::number(orderinfo.GetPrice()));
	edt_processcost->setText(QString::number(orderinfo.GetProcessCost()));
	edt_isshangrou->setText(orderinfo.GetIsShangRou() == true ? tr("yes") : tr("no"));
	edt_othercraftwork->setText(orderinfo.GetOtherCraftwork());
	edt_colortextilprintprice->setText(QString::number(orderinfo.GetColorTextilePrintPrice()));
	edt_gradeacount->setText(QString::number(orderinfo.GetGradeACount()));
	edt_gradebcount->setText(QString::number(orderinfo.GetGradeBCount()));
	edt_greyclothsuppiler->setText(orderinfo.GetGreyClothSupplier());
	edt_greyclothcount->setText(QString::number(orderinfo.GetGreyClothCount()));
	edt_greyclothprice->setText(QString::number(orderinfo.GetGreyClothPrice()));
	edt_memory->setText(orderinfo.GetMemory());
}

#include "moc_mainwindow.cpp"
