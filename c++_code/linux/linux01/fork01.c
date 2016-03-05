#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pid;
	pid = fork();
	if (-1 == pid) {
		printf("Create fork error.\n");
	}
	if (pid > 0) {
		printf("This is parent process, id is %d \n", getpid());
		sleep(10);
	}
	if (0 == pid) {
		printf("This is child process, parent id is %d\n", getppid());
		return 0;
	}
	return 0;
}
