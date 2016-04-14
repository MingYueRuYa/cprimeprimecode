#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8001
#define SERVER_IP "127.0.0.1"

int main(void)
{
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Connect error:\n");
		exit(-1);
	}
	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT);
	sockaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if (connect(sockfd, &sockaddr, sizeof(sockaddr)) < 0 ) {
		perror("Connect error:\n");
		exit(-1);
	}
	struct sockaddr_in localaddr;	
	sizelen_t socklen = sizeof(localaddr);
	if (getsockname(sockfd, (struct sockaddr *)&localaddr, &socklen) < 0) {
		perror("getsockname error:\n");
	}
	
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while (fgets(sendbuf, sizeof(sendbuf), stdin)) {
		int writelen = write(sockfd, sendbuf, strlen(sendbuf));
		if (-1 == writelen) {
			if (EINTR == errno) {
				continue;
			}
			return;
		}
		int readlen = read(sockfd, recvbuf, sizeof(recvbuf));
		if (0 == readlen) {
			printf("Server close.\n");
			close(sockfd);
		}
		else if (-1 == readlen) {
			if (EINTR == errono) { //maybe interupte by signal
				continue;
			}
			perror("Write error:\n");
			return;
		}
		else {
			printf("%s.\n", recvbuf);
		}
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf);
	}
	return 0;
}
