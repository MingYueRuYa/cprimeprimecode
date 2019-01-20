/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

#ifndef log4cpphelper_h
#define log4cpphelper_h

#include <string>
#include <stdarg.h>

#include "singleton.h"
#include "simpletimestamp.h"

#include <Appender.hh>
#include <Category.hh>
#include <Appender.hh>
#include <OstreamAppender.hh>
#include <Layout.hh>
#include <BasicLayout.hh>
#include <Priority.hh>
#include <FileAppender.hh>
#include <RollingFileAppender.hh>
#include <PatternLayout.hh>
#include <NDC.hh>

using std::string;

namespace XIBAO {

#define LOG_INITIALIZE(fileName) {\
		SINGLETON_INSTANCE(Log4cppHelper).Instance().Initialize(fileName); \
	}

#define LOG_INFO_ARGS(formatStr, ...) {\
        XIBAO::singleton::Singleton<Log4cppHelper>::Instance().LogInfo( \
			log4cpp::Priority::INFO, formatStr, __VA_ARGS__);  \
    }

#define LOG_NOTICE_ARGS(formatStr, ...) {\
        XIBAO::singleton::Singleton<Log4cppHelper>::Instance().LogInfo( \
				log4cpp::Priority::NOTICE, formatStr, __VA_ARGS__);  \
    }

#define LOG_WARN_ARGS(formatStr, ...) {\
        XIBAO::singleton::Singleton<Log4cppHelper>::Instance().LogInfo( \
				log4cpp::Priority::WARN, formatStr, __VA_ARGS__);  \
    }

#define LOG_ERROR_ARGS(formatStr, ...) {\
        XIBAO::singleton::Singleton<Log4cppHelper>::Instance().LogInfo( \
				log4cpp::Priority::ERROR, formatStr, __VA_ARGS__);  \
    }

#define LOG_CRIT_ARGS(formatStr, ...) {\
        XIBAO::singleton::Singleton<Log4cppHelper>::Instance().LogInfo( \
			log4cpp::Priority::CRIT, formatStr, __VA_ARGS__);  \
    }

#define LOG_ALTER_ARGS(formatStr, ...) {\
        XIBAO::singleton::Singleton<Log4cppHelper>::Instance().LogInfo( \
			log4cpp::Priority::ALERT, formatStr, __VA_ARGS__);  \
    }

#define LOG_INFO(msg) \
    XIBAO::singleton::Singleton<Log4cppHelper>::Instance().GetLogCategory() << \
    log4cpp::Priority::INFO << __FILE__ << " [" << __LINE__  << "] " << msg;

#define LOG_NOTICE(msg) \
    XIBAO::singleton::Singleton<Log4cppHelper>::Instance().GetLogCategory() << \
    log4cpp::Priority::NOTICE << __FILE__ << " [" << __LINE__  << "] " << msg;

#define LOG_WARN(msg) \
    XIBAO::singleton::Singleton<Log4cppHelper>::Instance().GetLogCategory() << \
    log4cpp::Priority::WARN << __FILE__ << " [" << __LINE__  << "] " << msg;

#define LOG_ERROR(msg) \
    XIBAO::singleton::Singleton<Log4cppHelper>::Instance().GetLogCategory() << \
    log4cpp::Priority::ERROR << __FILE__ << " [" << __LINE__  << "] " << \
    msg;

#define LOG_CRIT(msg) \
    XIBAO::singleton::Singleton<Log4cppHelper>::Instance().GetLogCategory() << \
    log4cpp::Priority::CRIT << __FILE__ << " [" << __LINE__  << "] " << msg;

#define LOG_ALERT(msg) \
    XIBAO::singleton::Singleton<Log4cppHelper>::Instance().GetLogCategory() << \
    log4cpp::Priority::ALERT << __FILE__ << " [" << __LINE__  << "] " << \
    msg;

class Log4cppHelper : SINGLETON_INHERIT(Log4cppHelper)
{
	DECLARE_PRIVATE_CONSTRUCTOR(Log4cppHelper, void)
	DECLARE_FRIEND_SINGLETON(Log4cppHelper)

public:
    ~Log4cppHelper();

    log4cpp::Category& GetLogCategory();

    void LogInfo(log4cpp::Priority::Value priority,
                 const char* stringFormat,
                 ...);
	void Initialize(const string &fileName);

private:
	string fileName_;

};

}

#endif // log4cpphelper_h