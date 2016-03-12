#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid = fork();
	int status;
	if (-1 == pid) {
		perror("Fork error:\n");	
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		sleep(100);
		printf("this is child prcess.\n");
		exit(100);
	}	


	//parent process
	if (pid > 0) {
		sleep(20);
		int ret = waitpid(pid, &status, WNOHANG);	
		printf("ret reslut is %d.\n", ret);
		if (WIFEXITED(status)) {
			printf("process exited %d.\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status)) {
			printf("process exited %d.\n", WTERMSIG(status));
		}
		else if (WIFSTOPPED(status)) {
			printf("process exited %d.\n", WSTOPSIG(status));
		}
		else {
			printf("Other way exited.\n");
		}
	}


	return 0;
}
