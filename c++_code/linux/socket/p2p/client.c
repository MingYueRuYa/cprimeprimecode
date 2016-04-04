#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define SERVER_PORT 8001
#define SERVER_IP "127.0.0.1"

int main(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		perror("Create socket error.\n");
		exit(-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	int connfd = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (-1 == connfd) {
		perror("Bind error.\n");
	}
	char sendbuffer[1024] = {0};
	char recvbuffer[1024] = {0};
	while (1) {
		if (fgets(sendbuffer, sizeof(sendbuffer), stdin) == NULL) {
			exit(0);
		}
		write(connfd, sendbuffer, strlen(sendbuffer));
		memset(sendbuffer, 0, sizeof(sendbuffer));
	}
	return 0;
}
