#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP 127.0.0.1
#define SERVER_PORT 8001

int main(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		perror("Socket error:\n");
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if (-1 == bind(sockfd, (struct sockaddr *)addr, sizeof(addr))) {
		perror("Bind error:\n");
		return -1;
	}
	if (-1 == listen(sockfd, SOMAXCONN)) {
		perror("Listen error:\n");
		return -1;
	}
	while (1) {
		struct sockaddr_in clientaddr;
		socklen_t socklen = 0;
		int connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &socklen);
		if (-1 == connfd) {
			perror("Accept error:\n");
			return -1;
		}
	}
		
	return 0;
}

