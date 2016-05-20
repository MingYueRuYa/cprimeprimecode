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

int main01(int argc, char *argv[])
{
	int pipefd[2] = {0};
	pid_t pid = 0;
	if (pipe(pipefd) < 0) {
		ERR_EXIT("pipe error:");
	}
	pid = fork();
	if (pid < 0) {
		ERR_EXIT("fork errro:");
	}
	else if (0 == pid) {
		//close read fd.
		close(pipefd[0]);
		if (write(pipefd[1], "hello ...", 6) < 0) {
			ERR_EXIT("child write error:");
		}
		close(pipefd[1]);
		printf("child exit.\n");
	}
	else if (pid > 0) {
		//close write fd;
		close(pipefd[1]);
		char tmpchar[100] = {0};
		int readlen = 0;
		if ((readlen = read(pipefd[0], tmpchar, sizeof(tmpchar))) < 0) {
			ERR_EXIT("child write error:");
		}
		printf("recv %s.\n", tmpchar);
		close(pipefd[0]);
		printf("parent exit.\n");
	}
	wait(NULL);
	return 0;
}


int main(int argc, char *argv[])
{
	//close stdin
	close(0);
	//Makefile become stdin
	open("Makefile", O_RDONLY);
	//close stdout
	close(1);
	//Makefile.bak become stdout
	open("Makefile.bak22", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//cat read stdin by readline and output to stdout
	execlp("cat", "cat", NULL);
	return 0;
}




