/*****************************************************************************
**
** 	Copyright (C) 2017 liushixiongcpp@163.com
**	All rights reserved.
**
*****************************************************************************/

#include "client_sock.h"

#include <errno.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <arap/inet.h>

#include <iostream>

using std::cout;
using std::endl;

ClientSock::ClientSock(const string &pIp, const int pPort)
	: mIp(pIp), mPort(pPort)

{
	mSockfd 	= -1;
	mIsClosed 	= false;
	
	//Init action
	if (mSockfd =socket(AF_INET, SOCK_STREAM, 0) < 0) {
		perror("Connect server error.\n");
		exit(-1);
	}

	struct sockaddr_in adrr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(mPort);
	addr.sin_addr.s_adrr = inet_addr(mIp.c_str());

	if (connect(mSockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Connect server error.\n");
		exit(-1);
	}
	
}

ClientSock::~ClientSock()
{
	Close();
}

void ClientSock::GetSockfd() const
{
	return mSockfd;
}

int ClientSock::SendMessage(const string &pMessage) const
{
	if (pMessage.empty()) {
		return 0;
	}

	int writelen = write(mSockfd, pMessage.c_str(), pMessage.length());
	if (-1 == writelen) {
		if (EINTR == errno) {
			continue;
		} else {
			perror("Send to server error.");
			Close();
		}
	}

	return writelen;
}

int ClientSock::RecevieMessage(string &pMessage) const
{
	char recvbuf[1024] = {0};
	int readlen = read(mSockfd, recvbuf, sizeof(recvbuf));
	if (0 == readlen) {
		cout << "server closed." << endl;
		Close();
	}
	else if (-1 == readlen) {
		cout << "server error." << endl;
		Close();
	}

	pMessage = string(recvbuf);
	return readlen;
}

bool ClientSock::Close()
{
	//close sockfd
	if (mSockfd == -1) {
		return false;
	}

	close(mSockfd);

	mSockfd 	= -1;
	mIsClosed 	= true;
	return true;
}

bool ClientSock::IsClosed()
{
	return mIsClosed;
}
