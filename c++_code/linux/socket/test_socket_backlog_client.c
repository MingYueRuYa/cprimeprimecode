/*
 * test socket half connect status(SYN_SEND)
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	int i = 0;
	for (; i < 1024 * 2 ; ++i) {
		printf("%d. \n", i);
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (-1 == sockfd) {
			perror("socket failed.");
			exit(-1);
		}
		struct sockaddr_in sockaddr;
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_port = htons(8001);
		sockaddr.sin_addr.s_addr = inet_addr("192.168.1.113");
		int optval = 1;
		int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
		if (- 1== ret) {
			perror("setsockopt error:");	
			return -1;
		}
		if ( -1 == connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr))) {
			perror("socket connect failed.");
			exit(-1);
		}
	}
	return 0;
}
