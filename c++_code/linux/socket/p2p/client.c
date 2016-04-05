/*
 * p2p client
 * need to tow process: one is read from stdin, other is write to server
 * 1.solve exception signal ->Ctrl+c
 * 2.parent process exit then child process should 
 * */
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

void IntHandler(int pSignalNum)
{
	printf("Receive signal number is %d.\n", pSignalNum);
	exit(0);
}

int main(void)
{
	signal(SIGINT, IntHandler);
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
	pid_t pid = fork();
	if (-1 == pid) {
		perror("Create process error:\n");
		exit(-1);
	}
	else if (0 == pid) { //child process responsibily to read from server
		while (1) {
			char recvbuffer[1024] = {0};
			int size = read(sockfd, recvbuffer, sizeof(recvbuffer));	
			if (-1 == size) {
				if (errno == EINTR) {
					continue;
				}
				perror("Read error:\n");
				kill(getppid(), SIGINT);
				exit(-1);
			}
			else if (0 == size) {
				printf("Server is close.\n");
				exit(0);
			}
			write(STDOUT_FILENO, recvbuffer, strlen(recvbuffer));
			memset(recvbuffer, 0, sizeof(recvbuffer));
		}
	}
	else if (pid > 0) { //parent process 
		char sendbuffer[1024] = {0};
		while (1) {
			if (fgets(sendbuffer, sizeof(sendbuffer), stdin) == NULL) {
				kill(pid, SIGINT);
				exit(0);
			}
			int size = write(sockfd, sendbuffer, strlen(sendbuffer));
			if (-1 == size) {
				if (errno == EINTR) {
					continue;
				}
			}
			if (0 == size) {
				kill(pid, SIGINT);
				printf("Write nothing to client.\n");
				exit(-1);	
			}
			memset(sendbuffer, 0, sizeof(sendbuffer));
		}
	}
	return 0;
}
