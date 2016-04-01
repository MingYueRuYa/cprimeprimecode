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
	int status = 0;
	while (wait(&status) > 0) {
		
	}
	printf("main exit.\n");
	return 0;
}
