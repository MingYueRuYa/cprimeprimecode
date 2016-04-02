#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * child process was create by parent.
 * */
int main(void)
{
	pid_t pid;
	int loops = 0, number = 0, i = 0, j = 0;
	printf("Input loops, number process.\n");	
	scanf("%d,%d", &loops, &number);
	for (; i < number; ++i ) {
		pid = fork();
		if (-1 == pid) {
			perror("fork error:");
			continue;
		}
		else if (pid > 0) {
			for (; j < loops; ++j) {
				printf("pid is %d, %d loop.\n", pid, j);	
			}
			exit(0);
		}
	}
	//think about waitpid function
	int status = 0;
	while (1) {
		int pid = waitpid(-1, &status, WNOHANG);
		if (-1 == pid) {
			break;
		}
		else if (WIFEXITED(status)) {
			printf("exit status %d.\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status)) {
			printf("killed by signal %d\n", WTERMSIG(status));
		} else if (WIFSTOPPED(status)) {
			printf("stopped by signal %d\n", WSTOPSIG(status));
		} else if (WIFCONTINUED(status)) {
			printf("continued\n");
		}
	}
//	while (1) {
//		int ret = wait(&status);		
//		if (-1 == ret) {
//			if (errno == EINTR) { //maybe wakeup by signal
//				continue;
//			}
//			break;
//		}
//	}
	printf("main exit.\n");
	return 0;
}
