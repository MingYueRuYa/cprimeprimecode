/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <string.h>

#include "udp_server.h"
#include "udp_server_config.h"

#ifdef OPEN_GLOG
	#include <glog/logging.h>
#endif 

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
#ifdef OPEN_GLOG
		LOG(ERROR) << strerror(errno);
#endif
		return false;
	}
	const int option = 1;
	//set broadcast type
	if (setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, (char *)&option, sizeof(option)) < 0) {
		//log and error reason
#ifdef OPEN_GLOG
		LOG(ERROR) << strerror(errno);
#endif
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
	char ipstr[1024] = "";
	GetLocalIp(ipstr, 1024);
	if (sendto(mSocket, ipstr, strlen(ipstr), 0, (sockaddr *)&mSocketAddr, sizeof(sockaddr_in)) < 0) {
#ifdef OPEN_GLOG
		LOG(ERROR) << strerror(errno);
#endif
		return false;
	}
#ifdef OPEN_GLOG
	LOG(INFO) << ipstr;
#endif
	return true;
}

bool UdpServer::GetLocalIp(char *pLocalIp, int pIpLen)
{
	struct ifaddrs *ifaddr, *ifa;
	int family, s;
	char host[NI_MAXHOST] = {0};

	if (getifaddrs(&ifaddr) == -1) {
#ifdef OPEN_GLOG
		LOG(ERROR) << strerror(errno);
#endif
		return false;
	}
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL) {
			continue;
		}
		family = ifa->ifa_addr->sa_family;
		if (family == AF_INET || family == AF_INET6) {
			s = getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
			if (0 != s) {
#ifdef OPEN_GLOG
				LOG(ERROR) << strerror(errno);
#endif
				return -1;
			}
			//background run
			if (strlen(pLocalIp) < (pIpLen - 1)) {
				strcat(pLocalIp, "-");
			}
			if (strlen(pLocalIp) < (pIpLen - strlen(host))) {
				strcat(pLocalIp, host);
			}
		}
	}
	freeifaddrs(ifaddr);
	return true;
}
