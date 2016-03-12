#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

void TestFunc(int loopcount)
{
	printf("loop %d\n", loopcount);
}

int main04(void)
{
	//僵尸进程 -> 子进程执行完之后，父进程没有进行收尸
	//孤儿进程 -> 就是父进程现执行完，但是子进程还没有结束，此时子进程的父进程就是1号进程 init进程
	//信号，告诉操作系统，我不收尸，然系统帮我收尸
	//忽视SIGCHLD的信号
	signal(SIGCHLD, SIG_IGN);
	pid_t pid;
	pid = fork();
	if (-1 == pid) {
		return 0;
	}
	if (pid > 0) {
		printf("parent process pid is %d.\n", getpid());
		sleep(20);
	}
	if (0 == pid) {
		printf("child process pid is %d, parent pid is %d.\n", getpid(), getppid());
		//sleep(100);
	}
	return 0;
}

int main(void)
{
	int threadcount = 10;
	int loopcount = 100;
	printf("plase input thread count:\n");
	scanf("%d", &threadcount);
	printf("plase input loop count:\n");
	scanf("%d", &loopcount);
	pid_t pid;
	int i, j;
	for (i = 0; i < threadcount; ++i) {
		pid = fork();
		if (-1 == pid) {
			return 1;
		}
		if (0 == pid) {
			for (j = 0; j < loopcount; ++j) {
				TestFunc(j);	
			}
			exit(0);
		}
	}
	while (1) {
		pid_t pid = wait(NULL);
		if (-1 == pid) {
			if (errno == EINTR ) {
				continue;
			}
			break;
		}
	}
	return 0;
}

int main02()
{
	fork();
	fork();
	fork();
	printf("hello\n");
	return 0;
}

int main01(void)
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

