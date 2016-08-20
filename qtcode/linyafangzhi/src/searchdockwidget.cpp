/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtGui/QPainter>

#include "searchdockwidget.h"

SearchDockWidget::SearchDockWidget(const OrderInfoList &pOrderInfoList, QWidget *pParent)
: QDockWidget(pParent)
{
	mOrderInfoList = pOrderInfoList;
	setProperty("Form", true);
	setupUi(this);

	UpdateUi();

	//connect(combo_dyework, SIGNAL(currentIndexChanged(const QString &)),this,
	//        SLOT(DoComDyeWorkChanged(const QString &)));
	//connect(combo_clientname, SIGNAL(currentIndexChanged(const QString &)),this,
	//        SLOT(DoComClientNameChanged(const QString &)));
	//connect(combo_specificationproducts, SIGNAL(currentIndexChanged(const QString &)), this,
	//        SLOT(DoComSpecficationProductsChanged(const QString &)));

	connect(btn_search, SIGNAL(clicked()), this, SLOT(DoSearch()));
}

SearchDockWidget::~SearchDockWidget()
{

}

OrderInfoList SearchDockWidget::FilterOrderInfo()
{
	OrderInfoList temporderinfolist;
	bool checkflag = false;
	QString dyeworkstr = "", clientnamestr = "", specificatiostr = "", supplierstr = "";
	
	//过滤染厂
	if (chb_dyework->isChecked()) {
		dyeworkstr = combo_dyework->currentText();
		if (dyeworkstr == tr("ALL")) {
			return mOrderInfoList;
		}
		foreach (OrderInfo info, mOrderInfoList) {
			if (info.GetDyeWork() != dyeworkstr) {
				continue;
			}
			temporderinfolist.append(info);
		}
	}

	//过滤客户名
	if (chb_clientname->isChecked()) {
		clientnamestr = combo_clientname->currentText();
		if (clientnamestr == tr("ALL")) {
			return mOrderInfoList;
		}
		for (int i = temporderinfolist.count() - 1; i >= 0; --i) {
			if (temporderinfolist[i].GetClientName() == clientnamestr) {
				continue;
			}
			temporderinfolist.removeAt(i);
		}
	}

	//过滤品名规格
	if (chb_specificationproducts->isChecked()) {
		specificatiostr = combo_specificationproducts->currentText();
		if (specificatiostr == tr("ALL")) {
			return mOrderInfoList;
		}
		for (int i = temporderinfolist.count() - 1; i >= 0; --i) {
			if (temporderinfolist[i].GetSpecificationProduct() == specificatiostr) {
				continue;
			}
			temporderinfolist.removeAt(i);
		}
	}
	
	//过滤供应商
	if (chb_supplier->isChecked()) {
		supplierstr = combo_supplier->currentText();
		if (supplierstr == tr("ALL")) {
			return mOrderInfoList;
		}
		for (int i = temporderinfolist.count() - 1; i >= 0; --i) {
			if (temporderinfolist[i].GetGreyClothSupplier() == supplierstr) {
				continue;
			}
			temporderinfolist.removeAt(i);
		}
	}

	return temporderinfolist;
}

void SearchDockWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setPen(Qt::blue);
	painter.drawRect(1, 1, width() - 2, height() - 2);
}

void SearchDockWidget::resizeEvent(QResizeEvent *)
{
	update();
}

void SearchDockWidget::UpdateUi()
{
	QSet<QString> dyeworkset, clientnameset, speficicationset, supplierset;
	foreach (OrderInfo info, mOrderInfoList) {
		if (! info.GetDyeWork().isEmpty()) {
			dyeworkset.insert(info.GetDyeWork());
		}
		if (! info.GetClientName().isEmpty()) {
			clientnameset.insert(info.GetClientName());
		}
		if (! info.GetSpecificationProduct().isEmpty()) {
			speficicationset.insert(info.GetSpecificationProduct());
		}
		if (! info.GetGreyClothSupplier().isEmpty()) {
			speficicationset.insert(info.GetGreyClothSupplier());
		}
	}
	QSet<QString>::iterator ibegin = dyeworkset.begin();
	while (ibegin != dyeworkset.end()) {
	    combo_dyework->addItem(*ibegin);
	    ++ibegin;
	}
	combo_dyework->addItem(tr("ALL"));

	ibegin = clientnameset.begin();
	while (ibegin != clientnameset.end()) {
	    combo_clientname->addItem(*ibegin);
	    ++ibegin;
	}
	combo_clientname->addItem(tr("ALL"));

	ibegin = speficicationset.begin();
	while (ibegin != speficicationset.end()) {
	    combo_specificationproducts->addItem(*ibegin);
	    ++ibegin;
	}
	combo_specificationproducts->addItem(tr("ALL"));

	ibegin = supplierset.begin();
	while (ibegin != supplierset.end()) {
		combo_supplier->addItem(*ibegin);
		++ibegin;
	}
	combo_supplier->addItem(tr("ALL"));
}

void SearchDockWidget::DoComDyeWorkChanged(const QString &pDyeWorkName)
{

}

void SearchDockWidget::DoComClientNameChanged(const QString &pClientName)
{

}

void SearchDockWidget::DoComSpecficationProductsChanged(const QString &pSepificationProducts)
{

}

void SearchDockWidget::DoSearch()
{
	emit OnOrderInfoSearched();
}

#include "moc_searchdockwidget.cpp"