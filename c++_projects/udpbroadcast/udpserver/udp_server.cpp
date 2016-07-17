/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <string.h>

#include "udp_server.h"

using std::cout;
using std::endl;
using std::string;

const int G_PORT = 6000;

UdpServer::UdpServer()
{
	mPort = G_PORT;
	mSocket = -1;
	bzero(&mSocketAddr, sizeof(sockaddr_in));
}

UdpServer::~UdpServer()
{
	close(mSocket);
	mSocket = -1;
}

bool UdpServer::Initialize()
{
	if ((mSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		cout << "socket function error." << endl;
		return false;
	}
	const int option = 1;
	//set broadcast type
	if (setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, (char *)&option, sizeof(option)) < 0) {
		//log and error reason
		cout << "setsockopt function error." << endl;
		return false;
	}
	mSocketAddr.sin_family = AF_INET;
	mSocketAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	mSocketAddr.sin_port = htons(mPort);
	return true;
}

bool UdpServer::Finalize()
{
	return false;
}

bool UdpServer::SendDatagram()
{
	string sendmsg = "hello";
	if (sendto(mSocket, sendmsg.c_str(), sendmsg.length(), 0, (sockaddr *)&mSocketAddr, sizeof(sockaddr_in)) < 0) {
		cout << "sendto function error." << endl;
		return false;
	}
	return true;
}
