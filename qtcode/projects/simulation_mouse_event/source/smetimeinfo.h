/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef smetimeinfo_h

#define smetimeinfo_h

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>

/*! \brief smeTimeInfo
    \author liushixiong (635672377@qq.com)
    \version 0.01
    \date 20016.09.03

    smeTimeInfo 定时信息类 
*/
class smeTimeInfo : public QObject
{
	Q_OBJECT

public:
	smeTimeInfo();

	~smeTimeInfo();

	bool SaveToXml();

	bool LoadFromXml();

	QTime GetTime();
	void SetTime(const QTime &pTime);

	int GetInterval();
	void SetInterval(const int &pInterval);

	int GetStartPositoin();
	void SetStartPosition(const int &pStartPosition);

	int GetEndPositoin();
	void SetEndPosition(const int &pEndPosition);

	int GetCount();
	void SetCount(const int &pCount);

	void StartTimer();
	void StopTimer();

protected:
	void timerEvent(QTimerEvent *pTimerEvent);

signals:
	void OnMouseClickEvent(const int &pStartPosition, const int &pEndStartPosition);

private:
	QTime mTime;

	int mInterval;

	int mStartPositoin;

	int mEndPosition;

	//鼠标点击的次数
	int mCount;

	int mTimer;

};

#endif //smetimeinfo_h