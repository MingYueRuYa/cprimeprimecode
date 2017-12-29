#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>          /* See NOTES */
#include <netinet/in.h>

#include "common.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{

	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == -1) {
		ERR_EXIT("socket");	
	}

	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family 	= AF_INET;	
	client.sin_port		= htons(5188);
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if (connect(sockfd, (struct sockaddr *)&client, sizeof(client)) < 0) {
		ERR_EXIT("connect");	
	}

	struct sockaddr_in localclient;
	memset(&localclient, 0, sizeof(localclient));
	socklen_t len = sizeof(localclient);
	if (getsockname(sockfd, (struct sockaddr *)&localclient, &len) < 0) {
		ERR_EXIT("getsockname");
	}

	cout << "ip:" << inet_ntoa(localclient.sin_addr) 
		 << " port:" << ntohs(localclient.sin_port)
		 << endl;

	 char recvbuf[1024] = {0};
	 char sendbuf[1024] = {0};
	while (NULL != fgets(sendbuf, 1024, stdin)) {
		if (write(sockfd, sendbuf, strlen(sendbuf)) < 0) {
			ERR_EXIT("write");
		}
	
		int readlen = read(sockfd, recvbuf, sizeof(recvbuf)/sizeof(char));
		if (readlen < 0) {
			ERR_EXIT("read");
		} else if (readlen == 0) {
			cout << "server closed" << endl;
			break;
		} else {
			cout << recvbuf;
		}
		memset(recvbuf, 0, sizeof(recvbuf)/sizeof(char));
		memset(sendbuf, 0, sizeof(recvbuf)/sizeof(char));
	}

	return 0;
}
