#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
	pid_t pid;
	int status;
	pid = fork();
	if (-1 == pid) {
		perror("Fork error:");
		exit(-1);
	}
	if (pid > 0) {
		pid = wait(&status);
		printf("child pid %d.\n", pid);
		if (WIFEXITED(status)) {
			printf("Exit code %d\n", WEXITSTATUS(status));
		}
	}
	if (pid == 0) {
		printf("this is child process, pid is %d.\n", getpid());
		sleep(3);
		//exit(3);
		return 4;
	}
	return 0;
}


