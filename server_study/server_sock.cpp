/*****************************************************************************
**
** 	Copyright (C) 2017 liushixiongcpp@163.com
**	All rights reserved.
**
*****************************************************************************/

#include "server_sock.h"

#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using std::string;

ServerSock::ServerSock(const string &pServerIp, const int pPort)
	: mServerIp(pServerIp), mPort(pPort)
{
	if (pServerIp.empty()) {
		cout << "ip address is empty." << endl;
		exit(-1);
	}

	if ((mSockfd = connect(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Scoket error.\n");
		exit(-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(mPort);
	addr.sin_addr.s_addr = inet_addr(mServerIp);
	int optval = -1;
	if (-1 == setsockopt(mSockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))) {
		perror("Set socket option error.\n");
		exit(-1);
	}

	if (-1 == bind(mSockfd, (struct sockaddr *)&addr, sizeof(addr))) {
		perror("bind error\n");
		exit(-1);
	}

	if (-1 == listen(mSockfd, SOMAXCONN)) {
		perror("listen error\n");
		exit(-1);
	}
}

ServerSock::~ServerSock()
{
}

int ServerSock::SendMessage(const string &pMessage) const
{
}

int ServerSock::RecevieMessage(string &pMessage) const
{
}

bool ServerSock::Close()
{
}

int ServerSock::Accept()
{
	struct sockaddr_in clientaddr;
	socklen_t socklen = sizeof(clientaddr);
	int connfd = accept(mSockfd, (struct sockaddr_in *)&clientaddr, &socklen);
}
