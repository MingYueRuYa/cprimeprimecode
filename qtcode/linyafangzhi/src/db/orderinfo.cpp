/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtSql/QSqlError>
#include <QtCore/QDebug>

#include "orderinfo.h"

bool OrderInfo::CreateTable()
{
	QSqlQuery query;
    query.prepare("CREATE TABLE orderinfo("
		"orderid INTEGER PRIMARY KEY,"
		"dyework VARCHAR,"
        "orderdate VARCHAR,"
		"clientname VARCHAR,"
		"clientcontact VARCHAR,"
        "specificationproduct VARCHAR,"
		"color VARCHAR,"
		"menfu VARCHAR,"
		"count INTEGER,"
		"price DOUBLE,"
		"processcost DOUBLE,"
		"shangrou BOOLEAN,"
		"othercraftwork VARCHAR,"
		"colortextilprintprice DOUBLE,"
		"gradeacount INTEGER,"
		"gradebcount INTEGER,"
		"greyclothsuppiler VARCHAR,"
		"greyclothcount INTEGER,"
        "greyclothprice DOUBLE,"
        "memory VARCHAR"
		")");
	if (! query.exec()) {
		return false;
	}
	return true;
}

bool OrderInfo::Delete(const int &pOrderInfoId)
{
	return true;
}

bool OrderInfo::GetOrderInfoList(OrderInfoList &pOrderInfoList)
{
	QSqlQuery query;
    query.prepare("SELECT orderid from orderinfo ORDER BY orderid");
	if (! query.exec()) {
		return false;
	}
	while (query.next()) {
		OrderInfo info;
		if (info.Load(query.value(0).toInt())) {
			continue;
		}
		pOrderInfoList.append(info);
	}
	return true;
}

OrderInfo::OrderInfo()
{
	mDyeWork = "";
    mOrderDate = "";
	mClientName = "";
	mClientContact = "";
	mSpecificationProduct = "";
	mGreyClothSupplier = "";
	mOtherCraftwork = "";
	mColorTextilePrintPrice = 0.0;
	mColor = "";
	mMenFu = "";
	mPrice = 0.0;
	mProcessCost = 0.0;
	mGreyClothPrice = 0.0;
	mCount = 0;
	mGradeACount = 0;
	mGradeBCount = 0;
	mGreyClothCount = 0;
	mIsShangRou = false;
    mMemory = "";
}

OrderInfo::~OrderInfo()
{

}

OrderInfo::OrderInfo(const OrderInfo &pOrderInfo)
{
	mOrderId  = pOrderInfo.mOrderId;
	mDyeWork = pOrderInfo.mDyeWork;
    mOrderDate = pOrderInfo.mOrderDate;
	mClientName = pOrderInfo.mClientName;
	mClientContact = pOrderInfo.mClientContact;
	mOrderDate = pOrderInfo.mOrderDate;
	mSpecificationProduct = pOrderInfo.mSpecificationProduct;
	mGreyClothSupplier = pOrderInfo.mGreyClothSupplier;
	mOtherCraftwork = pOrderInfo.mOtherCraftwork;
	mColorTextilePrintPrice = pOrderInfo.mColorTextilePrintPrice;
	mColor = pOrderInfo.mColor;
	mMenFu = pOrderInfo.mMenFu;
	mCount = pOrderInfo.mCount;
	mPrice = pOrderInfo.mPrice;
	mProcessCost = pOrderInfo.mProcessCost;
	mGreyClothPrice = pOrderInfo.mGreyClothPrice;
	mGradeACount = pOrderInfo.mGradeACount;
	mGradeBCount = pOrderInfo.mGradeBCount;
	mGreyClothCount = pOrderInfo.mGreyClothCount;
	mIsShangRou = pOrderInfo.mIsShangRou;
    mMemory = pOrderInfo.mMemory;
}

OrderInfo &OrderInfo::operator=(const OrderInfo &pOrderInfo)
{
	mOrderId  = pOrderInfo.mOrderId;
	mDyeWork = pOrderInfo.mDyeWork;
	mOrderDate = pOrderInfo.mOrderDate;
	mClientName = pOrderInfo.mClientName;
	mClientContact = pOrderInfo.mClientContact;
	mOrderDate = pOrderInfo.mOrderDate;
	mSpecificationProduct = pOrderInfo.mSpecificationProduct;
	mGreyClothSupplier = pOrderInfo.mGreyClothSupplier;
	mOtherCraftwork = pOrderInfo.mOtherCraftwork;
	mColorTextilePrintPrice = pOrderInfo.mColorTextilePrintPrice;
	mColor = pOrderInfo.mColor;
	mMenFu = pOrderInfo.mMenFu;
	mCount = pOrderInfo.mCount;
	mPrice = pOrderInfo.mPrice;
	mProcessCost = pOrderInfo.mProcessCost;
	mGreyClothPrice = pOrderInfo.mGreyClothPrice;
	mGradeACount = pOrderInfo.mGradeACount;
	mGradeBCount = pOrderInfo.mGradeBCount;
	mGreyClothCount = pOrderInfo.mGreyClothCount;
	mIsShangRou = pOrderInfo.mIsShangRou;
	mMemory = pOrderInfo.mMemory;
	return *this;
}

bool OrderInfo::Update()
{
	return true;
}

bool OrderInfo::Insert()
{
	return true;
}

bool OrderInfo::Load(const int &pOrderId)
{
    QSqlQuery query;
	query.prepare("SELECT "
        "dyework, orderdate, clientname, clientcontact, specificationproduct, color, menfu, count, "
        "price, processcost, shangrou, othercraftwork, colortextilprintprice, gradeacount, gradebcount, "
        "greyclothsuppiler, greyclothcount, greyclothprice, "
        "memory FROM orderinfo WHERE orderid=:orderid");
	query.bindValue(":orderid", pOrderId);
	if (! query.exec()) {
		return false;
	}
	mOrderId = pOrderId;
	mDyeWork = query.value(0).toString();
    mOrderDate = query.value(1).toString();
	mClientName = query.value(2).toString();
	mClientContact = query.value(3).toString();
	mSpecificationProduct = query.value(4).toString();
    mColor = query.value(5).toString();
    mMenFu = query.value(6).toString();
    mCount = query.value(7).toInt();
    mPrice = query.value(8).toDouble();
    mProcessCost = query.value(9).toDouble();
    mIsShangRou = query.value(10).toBool();
    mOtherCraftwork = query.value(11).toString();
    mColorTextilePrintPrice = query.value(12).toDouble();
    mGradeACount = query.value(13).toInt();
    mGradeBCount = query.value(14).toInt();
    mGreyClothSupplier = query.value(15).toString();
	mGreyClothCount = query.value(16).toInt();
    mGreyClothPrice = query.value(17).toDouble();
    mMemory = query.value(18).toString();
	return true;
}

#include "moc_orderinfo.cpp"

