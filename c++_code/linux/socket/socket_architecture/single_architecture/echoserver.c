#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8001

void SigchldHandler(int pSignal)
{
	int status;
	int pid = waitpid(-1,&status, WNOHANG);
	if (-1 == pid) {
		perror("Wait process error:\n");
		return;
	}
	else if (pid > 0) {
		printf("wait process pid is %d.\n", pid);
	}
}

int main(void)
{
	signal(SIGCHLD, SigchldHandler);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		perror("Socket error:\n");
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	int optval = 1;
	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))) {
		perror("Set socket option error:\n");
	}
	if (-1 == bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))) {
		perror("Bind error:\n");
		return -1;
	}
	if (-1 == listen(sockfd, SOMAXCONN)) {
		perror("Listen error:\n");
		return -1;
	}
	while (1) {
		struct sockaddr_in clientaddr;
		socklen_t socklen = sizeof(clientaddr);
		int connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &socklen);
		pid_t pid = fork();
		if (-1 == pid) {
			perror("Create process error:\n");
			exit(-1);	
		}
		else if (0 == pid) { //child process
			if (-1 == connfd) {
				perror("Accept error:\n");
				return -1;
			}
			printf("child process.\n");
			printf("client address %s.\n", inet_ntoa(clientaddr.sin_addr));
			while (1) {
				char recbuffer[1024] = {0};
				int readlen = read(connfd, recbuffer, sizeof(recbuffer));	
				if (-1 == readlen) {
					if (EINTR == errno) {
						continue;
					}
					//return - 1;
					exit(-1);
				}
				else if (0 == readlen) {
					printf("Client close.\n");
					close(connfd);
					exit(0);
				}
				else {
//					if (recbuffer[0] == 'c') {
//						close(connfd);
//						exit(0);
//					}
					printf("recv %s.\n", recbuffer);
					int writelen = write(connfd, recbuffer, strlen(recbuffer));
					if (-1 == writelen) {
						if (EINTR == errno) {
							continue;
						}
						close(connfd);
						//shutdown(connfd, SHUT_RDWR);
						exit(-1);
					}
					else if (writelen > 0) {
						//TODO something
					}
					else {
					}
					memset(recbuffer, 0, sizeof(recbuffer));
				}
			}
		}
		else if (pid > 0) { //parent process
			close(connfd);
		}
	}
	return 0;
}

