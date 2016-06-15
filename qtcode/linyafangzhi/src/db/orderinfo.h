/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef orderinfo_h
#define orderinfo_h

#include "baseinfo.h"

class OrderInfo : public BaseInfo
{
	Q_OBJECT

public:
	OrderInfo();

	~OrderInfo();

	QString GetDyeWork() { return mDyeWork; }
	void SetDyeWork(const QString &pDyeWork) { mDyeWork = pDyeWork;}

	QString GetOrderDate() { return mOrderDate; }
	void SetOrderDate(const QString &pOrderDate) { mOrderDate = pOrderDate;}

	QString GetClientName() { return mClientName; }
	void SetClientName(const QString &pClientName) { mClientName = pClientName;}

	QString GetClientContact() { return mClientContact; }
	void SetClientContact(const QString &pClientName) { mClientContact = pClientContact;}

	QString GetSpecificationProduct() { return mSpecificationProduct; }
	void SetSpecificationProduct(const QString &pSpecificationProduct) { mSpecificationProduct = pSpecificationProduct; }

	QString GetColor() { return mColor; }
	void SetColor(const QString &pColor) { mColor = pColor; }

	QString GetMenFu() { return mMenFu; }
	void SetMenFu(const QString &pMenFu) { mMenFu = pMenFu; }

	QString GetCount() { return mCount; }
	void SetCount(const QString &pCount) { mCount = pCount; }

	QString GetPrice() { return mPrice; }
	void SetPrice(const QString &pPrice) { mPrice = pPrice; }

	QString GetProcesCost() { return mProcesCost; }
	void SetProcesCost(const QString &pProcesCost) { mProcesCost = pProcesCost; }

	QString GetIsShangRou() { return mIsShangRou; }
	void SetIsShangRou(const QString &pIsShangRou) { mIsShangRou = pIsShangRou; }

	QString GetOtherCraftwork() { return mOtherCraftwork; }
	void SetOtherCraftwork(const QString &pOtherCraftwork) { mOtherCraftwork = pOtherCraftwork; }
	
	QString GetColorTextilePrintPrice() { return mColorTextilePrintPrice; }
	void SetColorTextilePrintPrice(const QString &pColorTextilePrintPrice) { mColorTextilePrintPrice = pColorTextilePrintPrice; }

	QString GetGradeA() { return mGradeA; }
	void SetGradeA(const QString &pGradeA) { mGradeA = pGradeA; }

	QString GetGradeB() { return mGradeB; }
	void SetGradeB(const QString &pGradeB) { mGradeB = pGradeB; }

	QString GetGreyClothSupplier() { return mGreyClothSupplier; }
	void SetGreyClothSupplier(const QString &pGreyClothSupplier) { mGradeB = pGreyClothSupplier; }

	QString GetGreyClothCount() { return mGreyClothCount; }
	void SetGreyClothCount(const QString &pGreyClothCount) { mGreyClothCount = pGreyClothCount; }

	QString GetGreyClothPrice() { return mGreyClothPrice; }
	void SetGreyClothPrice(const QString &pGreyClothPrice) { mGreyClothPrice = pGreyClothPrice; }

private:
	QString mDyeWork; //染场名称	

	QDate mOrderDate;

	QString mClientName;

	QString mClientContact;

	QString mSpecificationProduct;

	QString mColor;

	QString mMenFu; //门副

	QString mCount;

	double mPrice;

	double mProcesCost;//加工费

	bool mIsShangRou; //是否上柔

	QString mOtherCraftwork; //其他工艺

	QString mColorTextilePrintPrice; //染色/印花 单价	
	int mGradeA; //一等品

	int mGradeB; //次等品

	QString mGreyClothSupplier;

	int mGreyClothCount;

	double mGreyClothPrice;
};

#endif //orderinfo_h
