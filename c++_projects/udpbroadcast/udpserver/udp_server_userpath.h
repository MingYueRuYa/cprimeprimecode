/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef udp_server_userpath_h

#define udp_server_userpath_h

class UdpServerUserPath
{
public:
	UdpServerUserPath();

	~UdpServerUserPath();

	string GetUserPath();

private:
	string mUserPath;

};

#endif //udp_server_userpath_h
