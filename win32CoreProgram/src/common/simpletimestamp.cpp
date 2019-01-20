/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS

#include "simpletimestamp.h"

#include <stdio.h>
#include <time.h>
#include <inttypes.h>

namespace XIBAO {

	const string SimpleTimeStamp::DEFUALT_STYLE = "%4d%02d%02d %02d:%02d:%02d.%06d";
	const string SimpleTimeStamp::STRING_STYLE = "%4d%02d%02d%02d%02d%02d%06d";

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#ifdef WIN32
int gettimeofday(struct timeval *tp, void *tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year  = wtm.wYear - 1900;
    tm.tm_mon   = wtm.wMonth - 1;
    tm.tm_mday  = wtm.wDay;
    tm.tm_hour  = wtm.wHour;
    tm.tm_min   = wtm.wMinute;
    tm.tm_sec   = wtm.wSecond;
    tm.tm_isdst = -1;
    clock       = mktime(&tm);
    tp->tv_sec  = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}
#endif

string SimpleTimeStamp::toString() const
{
  char buf[32] = {0};
  int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
  int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
  _snprintf_s(buf, sizeof(buf)-1, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
  return buf;
}

string SimpleTimeStamp::toFormattedString(const string formatStyle, bool showMicroseconds) const
{
  char buf[32] = {0};
  time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
  struct tm tm_time;
  // msvc _gmtime64_s function is thread safe
  // linux always use gmtime_r that thread safe
  _gmtime64_s(&tm_time, &seconds);

  if (showMicroseconds)
  {
    int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
    _snprintf_s(buf, sizeof(buf), sizeof(buf), formatStyle.c_str(),
             tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
             tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
             microseconds);
  }
  else
  {
    _snprintf_s(buf, sizeof(buf), sizeof(buf), formatStyle.c_str(),
             tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
             tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
  }
  return buf;
}

SimpleTimeStamp SimpleTimeStamp::now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  int64_t seconds = tv.tv_sec;
  return SimpleTimeStamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}

}

#endif //__STDC_FORMAT_MACROS