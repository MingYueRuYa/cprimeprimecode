#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

void handler(int signum)
{
	if (signum == SIGINT) {
		printf("SIGINT num is %d.\n", signum);
	}
	else if (signum == SIGUSR1) {
		printf("recv SIGUSR1\n");
	}
	else {
		printf("recv signal num is %d.\n", signum);
	}
}

int main(void)
{
	pid_t pid;	
	int i = 0;
	printf("main...begin.\n");
	if (SIG_ERR == signal(SIGINT, handler)) {
		perror("func error\n");
		return -1;
	}
	if (SIG_ERR == signal(SIGUSR1, handler)) {
		perror("func error\n");
		return -1;
	}
	//注意这段代码产生了4个进程了
	for (; i < 2; ++i) {
		pid = fork();
		if (-1 == pid) {
			printf("fokr err...\n");
			continue;
		}
		printf("child process pid is %d.\n", pid);
	}
	
	//此段代码会调用两次
	if (0 == pid) {
		printf("child process.\n");
		//向父进程发送信号	
//		pid = getppid();
//		kill(pid, SIGUSR1);
		kill(0, SIGUSR1);
		pause();
	}	

	while (1) {
		int ret = wait(NULL);		
		if (-1 == ret) {
			if (errno == EINTR) {
				continue;
			}	
			break;
		}
	}
	return 0;
}
