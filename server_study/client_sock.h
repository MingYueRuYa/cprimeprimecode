/*****************************************************************************
**
** 	Copyright (C) 2017 liushixiongcpp@163.com
**	All rights reserved.
**
*****************************************************************************/

#ifndef client_sock_h
#define client_sock_h

#include <string>

using std::string;

/*! 封装sokcet请求
 *
 * 1.发送数据
 * 2.接收数据
 * */

class ClientSock
{
public:
	explicit ClientSock(const string &pIp, const int pPort);

	~ClientSock();

	void GetSockfd() const;

	int SendMessage(const string &pMessage) const;

	int RecevieMessage(string &pMessage) const;

	bool Close();

private:
	ClientSock(const ClientSock &pSock) {}

	ClientSock operator=(const ClientSock &pSock) {}

private:
	int mSockfd;

	int mPort;

	string mIp;

	bool mIsClosed;

};

#endif //sock_h
