/****************************************************************************
**
** Copyright (C) 2010 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "application.h"

#include <QtCore/QSettings>
#include <QtCore/QLocale>

Application::Application(int &argc, char **argv)
	: QApplication(argc, argv)
{
	mEnglishTranslator.load("volleyballstats_en", ":/i18n");
	mChineseSimplifiedQtTranslator.load("qt_zh_CN", ":/i18n/qt");
	mChineseSimplifiedTranslator.load("volleyballstats_zh_CN", ":/i18n");
	mChineseTraditionalQtTranslator.load("qt_zh_TW", ":/i18n/qt");
	mChineseTraditionalTranslator.load("volleyballstats_zh_TW", ":/i18n");

	//¼ÓÔØÄ¬ÈÏÓïÑÔ¡£
	QSettings settings("KazoVision", APPLICATION_NAME);
	mLanguage = settings.value("language", -1).toInt();
	if (mLanguage == -1) {
		QLocale locale;
		if (locale.country() == QLocale::China) {
			mLanguage = 1;
		}
		else if (locale.country() == QLocale::Taiwan || locale.country() == QLocale::HongKong) {
			mLanguage = 2;
		}
		else {
			mLanguage = 0;
		}
	}
	if (mLanguage == 1) {
		qApp->installTranslator(&mChineseSimplifiedQtTranslator);
		qApp->installTranslator(&mChineseSimplifiedTranslator);
	}
	else if (mLanguage == 2) {
		qApp->installTranslator(&mChineseTraditionalQtTranslator);
		qApp->installTranslator(&mChineseTraditionalTranslator);
	}
	else {
		qApp->installTranslator(&mEnglishTranslator);
	}

	UpdateManufacturerInfo();
	mEnableOemManufacturerInfo = false;
}

Application::~Application()
{
}

int Application::GetLanguage()
{
	return mLanguage;
}

void Application::SetLanguage(int language)
{
	this->removeTranslator(&mEnglishTranslator);
	this->removeTranslator(&mChineseSimplifiedQtTranslator);
	this->removeTranslator(&mChineseSimplifiedTranslator);
	this->removeTranslator(&mChineseTraditionalQtTranslator);
	this->removeTranslator(&mChineseTraditionalTranslator);
	if (language == 1) {
		this->installTranslator(&mChineseSimplifiedQtTranslator);
		this->installTranslator(&mChineseSimplifiedTranslator);
	}
	else if (language == 2) {
		this->installTranslator(&mChineseTraditionalQtTranslator);
		this->installTranslator(&mChineseTraditionalTranslator);
	}
	else {
		this->installTranslator(&mEnglishTranslator);
	}

	mLanguage = language;
	QSettings settings("KazoVision", APPLICATION_NAME);
	settings.setValue("language", mLanguage);

	UpdateManufacturerInfo();
}

void Application::UpdateManufacturerInfo()
{
	mManufacturerInfo.CompanyName = tr("Kazo Vision");
	mManufacturerInfo.CompanyLogo = ":/images/logo_kazo.png";
	mManufacturerInfo.CompanyUrl = tr("http://www.kazovision.com");
	mManufacturerInfo.Copyright = tr("Copyright(C) 2010-2015 Kazo Vision (<a href=\"http://www.kazovision.com\">http://www.kazovision.com</a>)");
}

void Application::SetOemManufacturerInfo(const QString &pCompanyName, const QString &pCompanyUrl, const QString &pCopyright)
{
	mEnableOemManufacturerInfo = true;
	mOemManufacturerInfo.CompanyName = pCompanyName;
	mOemManufacturerInfo.CompanyLogo = ":/images/logo_none.png";
	mOemManufacturerInfo.CompanyUrl = pCompanyUrl;
	mOemManufacturerInfo.Copyright = pCopyright;
}

ManufacturerInfo Application::GetManufacturerInfo() const
{
	if (mEnableOemManufacturerInfo) {
		return mOemManufacturerInfo;
	}
	return mManufacturerInfo;
}

#include "moc_application.cpp"
