/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#include "log4cpphelper.h"

namespace XIBAO {

Log4cppHelper::~Log4cppHelper()
{
    log4cpp::Category::shutdown();
}

void Log4cppHelper::LogInfo(log4cpp::Priority::Value priority,
                            const char* stringFormat,
                            ...)
{
    va_list va;

    va_start(va, stringFormat);
    log4cpp::Category::getInstance(fileName_).logva(
                                   priority, 
                                   stringFormat, 
                                   va);
    
    va_end(va);
}

log4cpp::Category& Log4cppHelper::GetLogCategory()
{
    return log4cpp::Category::getInstance(fileName_);
}

void Log4cppHelper::Initialize(const string &fileName)
{
	fileName_ = fileName;

    log4cpp::Appender *appender = new log4cpp::RollingFileAppender("default", 
                                      fileName_ +
									  XIBAO::SimpleTimeStamp::now().toFormattedString(
									  XIBAO::SimpleTimeStamp::STRING_STYLE) + string(".log")
                                  );
    log4cpp::PatternLayout *patternlayout = new log4cpp::PatternLayout();
    patternlayout->setConversionPattern("%d [%p] %m%n");
    appender->setLayout(patternlayout);

    log4cpp::Category& log = log4cpp::Category::getInstance(fileName_);
    log.addAppender(appender);
}

}