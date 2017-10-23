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

void echo_cli(int sockfd)
{
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	servaddr.sin_port = htons(SERVER_PORT);

	int ret = 0;
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};

	while (NULL != fgets(sendbuf, sizeof(sendbuf), stdin)) { //从命令行获取信息，阻塞形式
		//发送给服务器
		if (sendto(sockfd, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
			ERR_EXIT("sendto error:");
		}
		//阻塞，直到服务器返回
		if (recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, NULL, NULL) < 0) {
			if (EINTR == errno) {
				continue;
			}
			ERR_EXIT("recvfrom error:");
		}
		fputs(recvbuf, stdout);
		
		//收到quit时退出
		if (0 == strncasecmp(recvbuf, "quit", strlen("quit"))) {
			exit(0);
		}
		
		memset(sendbuf, 0 , sizeof(sendbuf));
		memset(recvbuf, 0 , sizeof(recvbuf));
	}
	close(sockfd);
}

int main(void)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		ERR_EXIT("socket error:");
	}
	echo_cli(sockfd);
	return 0;
}
