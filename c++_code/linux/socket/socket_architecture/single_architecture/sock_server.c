#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#include "sockutil.h"

void handle(int signum)
{
	int pid = 0;
	while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) {
		printf("child process %d exited.\n", pid);
	}
}

int main(void)
{
	int ret = 0;
	int listenfd;

	signal(SIGCHLD, handle);
	signal(SIGPIPE, SIG_IGN);

	if (sckServer_init(8001, &listenfd) < 0) {
		printf("sckServer_init() error:\n");
		return -1;
	}

	while (1) {
		int ret = 0;
		int wait_second = 0;
		int connfd = 0;

		ret = sckServer_accept(listenfd, &connfd, wait_second);
		if (ret == SOCKET_ERROR_TIMEOUT) {
			printf("timeout...\n");
			continue;
		}
		printf("client connected.\n");
		int pid = fork();
		if (pid < 0) {
			continue;
		}
		else if (0 == pid) {
			char recvbuff[1024];
			int recvbuflen = 1024;
			close(listenfd);
			while (1) {
				memset(recvbuff, 0, 1024);
				//ret = sckServer_rec(connfd, recvbuff, &recvbuflen, 0);
				ret = sckServer_send(connfd, recvbuff, strlen(recvbuff), 0);
				//ret = read(connfd, recvbuff, recvbuflen);
				if (ret < 0) {
					printf("sckServer_rec error:\n");
					break;
				}
				else if (ret == 0) {
					printf("client close.\n");
					break;
				}
				else {
					printf("recv %s.\n", recvbuff);
				}
				//ret = sckServer_send(connfd, recvbuff, strlen(recvbuff), 0);
				ret = write(connfd, recvbuff, strlen(recvbuff));
				if (ret < 0) {
					perror("sckServer_send error");
					break;
				}
			}	
			close(connfd);
			exit(ret);
		}
		else if (pid > 0) {
			close(connfd);
		}
	}

	return 0;
}
