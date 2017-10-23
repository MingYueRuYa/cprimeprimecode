#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8002

#define ERR_EXIT(m) \
	do { \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while (0)

void echo_srv(int sockfd)
{
	char recvbuf[1024] = {0};
	struct sockaddr_in peeraddr;
	socklen_t peerlen;
	int n;
	while (1) {
		peerlen = sizeof(peeraddr);
		memset(&peeraddr, 0, sizeof(peeraddr));
		n = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&peeraddr, &peerlen);
		if (-1 == n) {
			if (EINTR == errno) {
				continue;
			}
			ERR_EXIT("recvfrom  error:");
		}
		else if (n > 0) {
			int ret = 0;	
			fputs(recvbuf, stdout);
			ret = sendto(sockfd, recvbuf, n, 0, (struct sockaddr *)&peeraddr, peerlen);
			//收到quit时退出
			if (0 == strncasecmp(recvbuf, "quit", strlen("quit"))) {
				exit(0);
			}
		}
		//每次清空缓冲区的内容
		memset(recvbuf, 0, sizeof(recvbuf));
	}
	close(sockfd);
}


int main(void)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		ERR_EXIT("socket error:");	
	}
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		ERR_EXIT("bind error:");
	}
	echo_srv(sockfd);
	return 0;
}
