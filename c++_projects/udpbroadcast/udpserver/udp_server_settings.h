/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef udp_server_settings_h

#define udp_server_settings_h

class UdpServerSettings
{
public:
	static bool Initialize();

	static bool Finalize();

	static UdpServerSettings* GetSettingsInstance();

	int GetSleepTime();

	int GetLoopCount();

private:
	UdpServerSettings();

	~UdpServerSettings();

private:
	static UdpServerSettings *mThis;

	//send datagram interval time.
	int mSleepTime;	

	//if occur unkown error, not exit immediately.try more time. 
	int mLoopCount;

};

#endif //udp_server_settings_h
