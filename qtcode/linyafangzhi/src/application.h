/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef application_h
#define application_h

#include <QtCore/QVariant>
#include <QtCore/QTranslator>
#include <QtGui/QApplication>

#include "config.h"

typedef struct
{
	QString CompanyName;
	QString CompanyLogo;
	QString CompanyUrl;
	QString Copyright;
} ManufacturerInfo;

class Application : public QApplication
{
	Q_OBJECT

public:
	Application(int &argc, char **argv);

	~Application();

	int GetLanguage();

	void SetLanguage(int language);

	void UpdateManufacturerInfo();

	void SetOemManufacturerInfo(const QString &pCompanyName, const QString &pCompanyUrl, const QString &pCopyright);

	ManufacturerInfo GetManufacturerInfo() const;

private:
	QTranslator mEnglishTranslator;

	QTranslator mChineseSimplifiedQtTranslator;
	QTranslator mChineseSimplifiedTranslator;

	QTranslator mChineseTraditionalQtTranslator;
	QTranslator mChineseTraditionalTranslator;

	int mLanguage;

	ManufacturerInfo mManufacturerInfo;

	bool mEnableOemManufacturerInfo;

	ManufacturerInfo mOemManufacturerInfo;

};

#endif //application_h
