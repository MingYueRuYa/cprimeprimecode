/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef orderinfo_h
#define orderinfo_h

#include <QtCore/QDate>

#include "baseinfo.h"

class OrderInfo;
typedef QList<OrderInfo> OrderInfoList;

class OrderInfo : public BaseInfo
{
	Q_OBJECT

public:
    static bool CreateTable();

    static bool Delete(const int &pOrderInfoId);

    static bool GetOrderInfoList(OrderInfoList &pOrderInfoList);

public:
	OrderInfo();

	~OrderInfo();

	OrderInfo(const OrderInfo &pOrderInfo);

	OrderInfo &operator=(const OrderInfo &pOrderInfo);

	bool Update();

	bool Insert();

	bool Load(const int &pOrderId);

	int GetOrderId() const { return mOrderId; }
	void SetOrderId(const int &pOrderId) { mOrderId = pOrderId; }

	QString GetDyeWork() const { return mDyeWork; }
	void SetDyeWork(const QString &pDyeWork) { mDyeWork = pDyeWork;}

    QString GetOrderDate() const { return mOrderDate; }
    void SetOrderDate(const QString &pOrderDate) { mOrderDate = pOrderDate;}

	QString GetClientName() const { return mClientName; }
	void SetClientName(const QString &pClientName) { mClientName = pClientName;}

	QString GetClientContact() const { return mClientContact; }
	void SetClientContact(const QString &pClientContact) { mClientContact = pClientContact;}

	QString GetSpecificationProduct() const { return mSpecificationProduct; }
	void SetSpecificationProduct(const QString &pSpecificationProduct) { mSpecificationProduct = pSpecificationProduct; }

	QString GetColor() const { return mColor; }
	void SetColor(const QString &pColor) { mColor = pColor; }

	QString GetMenFu() const { return mMenFu; }
	void SetMenFu(const QString &pMenFu) { mMenFu = pMenFu; }

	int GetCount() const { return mCount; }
	void SetCount(const int &pCount) { mCount = pCount; }

	double GetPrice() const { return mPrice; }
	void SetPrice(const double &pPrice) { mPrice = pPrice; }

	double GetProcessCost() const { return mProcessCost; }
	void SetProcessCost(const double &pProcessCost) { mProcessCost = pProcessCost; }

	bool GetIsShangRou() const { return mIsShangRou; }
	void SetIsShangRou(const bool &pIsShangRou) { mIsShangRou = pIsShangRou; }

	QString GetOtherCraftwork() const { return mOtherCraftwork; }
	void SetOtherCraftwork(const QString &pOtherCraftwork) { mOtherCraftwork = pOtherCraftwork; }
	
	double GetColorTextilePrintPrice() const { return mColorTextilePrintPrice; }
	void SetColorTextilePrintPrice(const double &pColorTextilePrintPrice) { mColorTextilePrintPrice = pColorTextilePrintPrice; }

	int GetGradeACount() const { return mGradeACount; }
	void SetGradeACount(const int &pGradeACount) { mGradeACount = pGradeACount; }

	int GetGradeBCount() const { return mGradeBCount; }
	void SetGradeBCount(const int &pGradeBCount) { mGradeBCount = pGradeBCount; }

	QString GetGreyClothSupplier() const { return mGreyClothSupplier; }
	void SetGreyClothSupplier(const QString &pGreyClothSupplier) { mGreyClothSupplier = pGreyClothSupplier; }

	int GetGreyClothCount() const { return mGreyClothCount; }
	void SetGreyClothCount(const int &pGreyClothCount) { mGreyClothCount = pGreyClothCount; }

	double GetGreyClothPrice() const { return mGreyClothPrice; }
	void SetGreyClothPrice(const double &pGreyClothPrice) { mGreyClothPrice = pGreyClothPrice; }

    QString GetMemory() const { return mMemory; }
    void SetMemory(const QString &pMemory) { mMemory = pMemory; }

private:
	int mOrderId;

	QString mDyeWork; //染场名称	

    QString mOrderDate;

	QString mClientName;

	QString mClientContact;

	QString mSpecificationProduct;

	QString mColor;

	QString mMenFu; //门副

	int mCount;

	double mPrice;

	double mProcessCost;//加工费

	bool mIsShangRou; //是否上柔

	QString mOtherCraftwork; //其他工艺

	double mColorTextilePrintPrice; //染色/印花 单价	

	int mGradeACount; //一等品

	int mGradeBCount; //次等品

	QString mGreyClothSupplier;

	int mGreyClothCount;

	double mGreyClothPrice;

    QString mMemory; //备注
};

#endif //orderinfo_h
