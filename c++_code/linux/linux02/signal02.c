#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

void handler(int signum)
{
	printf("signal num is %d.\n", signum);
}

void handler02(int signum)
{
	printf("hello world.\n");
}

//测试函数的返回值
int main(void)
{
	//返回上一次设置的handler
	__sighandler_t old = signal(SIGINT, handler);
	if (old == SIG_ERR) {
		printf("Install signal error.\n");
	}
	while (getchar() != 'a') {
		pause();
		printf("main process paused.\n");
	}
	__sighandler_t old2 = signal(SIGINT, handler02);
	//old2(2);
	while (getchar() != 'a') {
		pause();
		printf("main process paused.\n");
	}
	signal(SIGINT, old2);
	while (1)  {
		pause();
	}
	return 0;
}

int main02(void)
{
	signal(SIGINT, handler);
	char tmpchar;
	while ((tmpchar = getchar()) != 'a') {
		pause();
		printf("main process paused.\n");
	}
	signal(SIGINT, SIG_DFL);
	return 0;
}

int main01(void)
{
	signal(SIGCHLD, handler);
	pid_t pid;
	pid = fork();
	if (0 == pid) {
		printf("child process existed.\n");
		exit(0);
	}
	while(1) {
		pause();
		printf("main process paused.\n");
	}
	printf("main process existed.\n");
	return 0;
}
