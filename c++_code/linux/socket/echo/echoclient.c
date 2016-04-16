#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8001
#define SERVER_IP "127.0.0.1"

int global_sockfd;

void SigHandler(int pSignal, siginfo_t *pSiginfo, void *pVoid)
{
	if (SIGINT == pSignal) {
		close(global_sockfd);
		printf("Close client.\n");
		exit(0);
	}
}

int main(void)
{
	struct sigaction act;
	act.sa_sigaction = SigHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	if ((global_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Connect error:\n");
		exit(-1);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if (connect(global_sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0 ) {
		perror("Connect error:\n");
		exit(-1);
	}
	/*
	struct sockaddr_in localaddr;	
	socklen_t socklen = sizeof(localaddr);
	if (getsockname(sockfd, (struct sockaddr *)&localaddr, &socklen) < 0) {
		perror("getsockname error:\n");
	}
	*/
	
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	while (fgets(sendbuf, sizeof(sendbuf), stdin)) {
		int writelen = write(global_sockfd, sendbuf, strlen(sendbuf));
		if (-1 == writelen) {
			if (EINTR == errno) {
				continue;
			}
			return -1;
		}
		int readlen = read(global_sockfd, recvbuf, sizeof(recvbuf));
		if (0 == readlen) {
			printf("Server close.\n");
			close(global_sockfd);
		}
		else if (-1 == readlen) {
			if (EINTR == errno) { //maybe interupte by signal
				continue;
			}
			perror("Write error:\n");
			return -1;
		}
		else {
			printf("%s", recvbuf);
		}
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
	}
	return 0;
}
