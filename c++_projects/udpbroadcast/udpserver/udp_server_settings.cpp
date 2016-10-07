/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifdef OPEN_GLOG
	#include <glog/loging.h>
#endif

#include "udp_server_settings.h"

UdpServerSettings* UdpServerSettings::mThis = nullptr;

bool UdpServerSettings::Initialize()
{
	if (nullptr == mThis) {
		mThis = new UdpServerSettings();	
	}
	return true;
}

bool UdpServerSettings::Finalize()
{
	if (nullptr != mThis) {
		delete mThis;
		mThis = nullptr;
	}
	return true;
}

UdpServerSettings* UdpServerSettings::GetSettingsInstance()
{
	return mThis;
}

int UdpServerSettings::GetSleepTime()
{
	return mSleepTime;
}

int UdpServerSettings::GetLoopCount()
{
	return mLoopCount;
}

UdpServerSettings::UdpServerSettings()
{
	mSleepTime = 5;
	mLoopCount = 10;
}


UdpServerSettings::~UdpServerSettings()
{
}

