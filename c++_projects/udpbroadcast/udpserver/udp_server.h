/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef udp_server_h

#define udp_server_h

#include <iostream>

#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>

class UdpServer 
{
public:
	UdpServer();

	~UdpServer();

	bool Initialize();

	bool Finalize();

	bool SendDatagram();
	
private:
	bool GetLocalIp(char *pLocalIp, int pIpLen);

private:
	int mPort;

	int mSocket;

	struct sockaddr_in mSocketAddr;

};

#endif //udp_server_h
