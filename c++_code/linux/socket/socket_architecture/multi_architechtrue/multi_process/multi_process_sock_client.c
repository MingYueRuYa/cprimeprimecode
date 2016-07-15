
#ifndef sock_client_h
#define sock_client_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include <sys/wait.h>

#include "sockutil.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8001
#define RECV_BUFFER_SIZE 1024

int main(void)
{
	signal(SIGPIPE, SIG_IGN);
	void *handle = NULL;	
	int connfd = 0;
	char *data = "linux is very good!";

	int processcount = 0;
	printf("please intput process count:");
	scanf("%d.\n", &processcount);
	int ret = sckClient_init(&handle, 30, 30, 30, 10);
	if (0 != ret) {
		printf("Init error code %d.\n", ret);
		return ret;
	}

	int i = 0;
	for (; i < processcount; ++i) {
		pid_t pid = fork();
		//child process
		if (0 == pid) {
			ret = sckClient_getconn(handle, SERVER_IP, SERVER_PORT, &connfd);
			if (0 != ret) {
				printf("Getconn error code %d.\n", ret);
				perror("Getconn error");
				return ret;
			}
			ret = sckClient_send(handle, connfd, (unsigned char *)data, strlen(data));
			if (0 != ret) {
				printf("Send error code %d.\n", ret);
				perror("Send error");
				return ret;
			}
			unsigned char buffer[RECV_BUFFER_SIZE] = {0};
			ret = sckClient_recv(handle, connfd, buffer, sizeof(buffer));
			if (0 != ret) {
				printf("Recvie error code %d.\n", ret);
				perror("Recvie error:\n");
				return ret;
			}
			printf("recv....\n");
			printf("%s", buffer);

			sckClient_closeconn(&connfd);
			exit(0);
		}
	}
	sckClient_destory(&handle);
	while (1) {
		int pid = 0;
		if ((pid = waitpid(-1, NULL, WNOHANG) < 0)) {
			break;
		}
//		printf("child process pid %d exit.\n", pid);
	}
	return 0;
}

#endif //sock_client_h
