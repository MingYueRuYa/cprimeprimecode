/*
 * 实现在读取文件的屏蔽int和quit信号，读完之后在恢复信号
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <error.h>

void BlockSignal()
{
	sigset_t sigset;	
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGQUIT);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
}

void UnBlockSignal()
{
	sigset_t sigset;	
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGQUIT);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
}

void Handler(int signum/*, siginfo_t *info, void *useless*/)
{
	printf("signum %d.\n", signum);
}

int main(void)
{
	BlockSignal();	

	int sleeptime = 5;
	do {	
		int fd = open("./hello.txt", O_RDONLY);
		if (-1 == fd) {
			perror("open file error.");
			exit(-1);
		}
		char ch[1024] = {0};
		int len = read(fd, ch, sizeof(ch));
		if (-1 == len) {
			perror("open file error.");
			exit(-1);
		}
		else if (0 == len) {
			printf("read over.\n");
		}
		write(STDOUT_FILENO, ch, strlen(ch));
	} while ( sleeptime = sleep(sleeptime));
	UnBlockSignal();
	printf("unblock sigint.\n");
	signal(SIGINT, Handler);
//	struct sigaction action;
//	action.sa_sigaction = Handler;	
//	sigaction(SIGINT, &action, NULL);
//	action.sa_flags = SA_SIGINFO;
//	struct siginfo_t info;
//	info.si_int = 100001;
	while (1) {

	}
	return 0;
}
