/*****************************************************************************
**
** 	Copyright (C) 2017 liushixiongcpp@163.com
**	All rights reserved.
**
*****************************************************************************/

#ifndef server_sock_h
#define server_sock_h

class ServerSock
{
public:
	ServerSock(const string &pServerIp, const int pPort);

	~ServerSock();

	int SendMessage(const string &pMessage) const;

	int RecevieMessage(string &pMessage) const;

	bool Close();

	int Accept();

private:
	ServerSock(const ServerSock &pSock) {}

	ServerSock operator=(const ServerSock &pSock) {}

private:
	string mServerIp;

	int mPort;

	int mSockfd;

};

#endif //server_sock_h
