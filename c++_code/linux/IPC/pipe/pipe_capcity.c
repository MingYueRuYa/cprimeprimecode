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
	char buf[1024 * 5];
	memset(&buf, 'A', sizeof(buf));
	int i = 0;
	while (1) {
		write(pipefd[1], buf, 512);
		printf("number %d.\n", ++i);
	}
	return 0;
}
