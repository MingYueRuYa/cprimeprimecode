/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <sys/wait.h>

#define ERR_EXIT(msg) \
		do { \
			perror(msg); \
			exit(EXIT_FAILURE); \
		} while(0)

int main(int argc, char *argv[])
{
	int pipefd[2];
	if (pipe(pipefd) < 0) {
		perror("pipe error");
		return -1;
	}
	pid_t pid = fork();
	if (pid < 0) {
		perror("fokr error");
		return -1;
	}
	else if (0 == pid) {
		sleep(5);
		close(pipefd[0]);
		if (4 != write(pipefd[1], "this is linux os.", 4)) {
			perror("write error");
		}
		close(pipefd[1]);
		exit(0);
	}
	else if (pid > 0) {
		int flag = fcntl(pipefd[0], F_GETFL);
		if (flag < 0) {
			perror("fcntl error");
			return -1;
		}
		flag = flag | O_NONBLOCK;
		if (fcntl(pipefd[0], F_SETFL, flag) < 0) {
			perror("fcntl error");
			return -1;
		}
		close(pipefd[1]);	
		char buf[512] = {0};
		if (read(pipefd[0], buf, sizeof(buf)) < 0) {
			perror("read error");
			printf("error name %s.\n", strerror(errno));
			return -1;
		}
		printf("recv from child %s.\n", buf);
		close(pipefd[0]);
	}
	return 0;
}
