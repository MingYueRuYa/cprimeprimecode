/*
 * p2p server
 * tow process: one read from stdin, other is write to client. 
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define SERVER_PORT 8001
#define SERVER_IP "127.0.0.1"

void SigIntHandler(int pSigNum)
{
	printf("Receive signal number is %d.\n", pSigNum);
	exit(0);
}

int main(void)
{
	signal(SIGINT, SigIntHandler);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		perror("Create socket error.\n");
		exit(-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	int optval = 1;
	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))) {
		perror("Set sockopt error.\n");
		exit(-1);
	}
	if (-1 == bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))) {
		perror("Bind error.\n");
		exit(-1);
	}
	
	if (-1 == listen(sockfd, SOMAXCONN)) { //max file descriptor
		perror("Listen error.\n");
		exit(-1);
	}
	struct sockaddr_in accepaddr;
	socklen_t size = 0;
	int connfd = accept(sockfd, (struct sockaddr *)&accepaddr, &size);
	printf("Accept client.\n");
	if (-1 == connfd) {
		perror("Accept error.\n");
		exit(-1);
	}
	pid_t pid = fork();
	if (-1 == pid) {
		perror("Fork error:\n");
		exit(-1);
	}
	else if (0 == pid) { //child process
		close(sockfd);
		char recvbuffer[1024] = {0};
		while (1) {
			int size = read(connfd, recvbuffer, sizeof(recvbuffer));	
			if (0 == size) {
				printf("Client exit.\n");
				kill(getppid(), SIGINT);
				close(connfd);
				exit(0);
			}
			if (-1 == size) {
				if (errno == EINTR) { //interrupt by signal
					continue;
				}
			}
			write(STDOUT_FILENO, recvbuffer, strlen(recvbuffer));
			memset(recvbuffer, 0, sizeof(recvbuffer));
		}
	}
	else if (pid > 0) { //parent process
		char recvbuffer[1024] = {0};
		while (1) {
			int size = read(STDIN_FILENO, recvbuffer, sizeof(recvbuffer));
			if (0 == size) {
				printf("Client exit.\n");
				kill(pid, SIGINT);
				close(sockfd);
				close(connfd);
				exit(0);
			}
			if (-1 == size) {
				if (errno == EINTR) { //interrupt by signal
					continue;
				}
			}
			write(connfd, recvbuffer, strlen(recvbuffer));
			memset(recvbuffer, 0, sizeof(recvbuffer));
		}
	}
	close(sockfd);
	return 0;
}
