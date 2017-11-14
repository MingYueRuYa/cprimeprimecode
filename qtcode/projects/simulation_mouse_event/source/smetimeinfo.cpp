/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtCore/QFile>
#include <QtXml/QDomDocument>

#include "smetimeinfo.h"

int G_Count = 0;

smeTimeInfo::smeTimeInfo()
{
	mTime = QTime(0, 0);
	mInterval = -1;
	mStartPositoin = 0;
	mEndPosition = 0;
	mCount = 0;
	mTimer = 0;
}

smeTimeInfo::~smeTimeInfo()
{
	StopTimer();
}

bool smeTimeInfo::SaveToXml()
{

	return true;
}

bool smeTimeInfo::LoadFromXml()
{
	return true;
}

QTime smeTimeInfo::GetTime()
{
	return mTime;
}

void smeTimeInfo::SetTime(const QTime &pTime)
{
	mTime = pTime;
}

int smeTimeInfo::GetInterval()
{
	return mInterval;
}

void smeTimeInfo::SetInterval(const int &pInterval)
{
	mInterval = pInterval;
}

int smeTimeInfo::GetStartPositoin()
{
	return mStartPositoin;
}

void smeTimeInfo::SetStartPosition(const int &pStartPosition)
{
	mStartPositoin = pStartPosition;
}

int smeTimeInfo::GetEndPositoin()
{
	return mEndPosition;
}

void smeTimeInfo::SetEndPosition(const int &pEndPosition)
{
	mEndPosition = pEndPosition;
}

int smeTimeInfo::GetCount()
{
	return mCount;
}

void smeTimeInfo::SetCount(const int &pCount)
{
	mCount = pCount;
	G_Count = mCount;
}

void smeTimeInfo::StartTimer()
{
	StopTimer();
	G_Count = mCount;
	if (mInterval <= 0) {
		return;
	}
	mTimer = startTimer(mInterval);
}

void smeTimeInfo::StopTimer()
{
	if (0 != mTimer) {
		killTimer(mTimer);
		mTimer = 0;
	}
}

void smeTimeInfo::timerEvent(QTimerEvent *pTimerEvent)
{
	if (mInterval <= 0) {
		StopTimer();
		return;
	}

	if (G_Count-- <= 0) {
		StopTimer();
		return;
	}

	//QTime(0, 0, 0) 表示0，立即执行
	if ( (mTime == QTime(0, 0, 0)) || ( mTime < QTime::currentTime() && mTime != QTime(0, 0, 0) )) {
		emit OnMouseClickEvent(mStartPositoin, mEndPosition);
	}
}

#include "moc_smetimeinfo.cpp "