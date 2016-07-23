/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include "glogencapsulation.h"

//this macro should be in application config file.
const string G_APPLICATION_NAME = "test";

glogEncapsulation* glogEncapsulation::mThis = NULL;

bool glogEncapsulation::Initialize()
{
	if (NULL != mThis) {
		return true;
	}
	mThis = new glogEncapsulation();
	return true;
}

bool glogEncapsulation::Finalize()
{
	if (NULL != mThis) {
		delete mThis;
		mThis = NULL;
	}
	return true;
}

void glogEncapsulation::Info(const string &pInfoMsg)
{
	LOG(INFO) << pInfoMsg;
}

void glogEncapsulation::Warning(const string &pWarningMsg)
{
	LOG(WARNING) << pWarningMsg;
}

void glogEncapsulation::Error(const string &pErrorMsg)
{
	LOG(ERROR) << pErrorMsg;
}

void glogEncapsulation::Fatal(const string &pFatalMsg)
{
	LOG(FATAL) << pFatalMsg;
}

glogEncapsulation::glogEncapsulation()
{
	google::InitGoogleLogging(G_APPLICATION_NAME.c_str());
}

glogEncapsulation::~glogEncapsulation()
{
	google::ShutdownGoogleLogging();
}

