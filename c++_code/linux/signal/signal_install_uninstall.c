/*
 * 信号的安装和卸载
 * 	经过测试发现信号的未决状态不能放在回调函数中
 * */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void IntHandler(int signum)
{
	printf("Recv signal num is %d.\n", signum);
}

void QuitHandler(int signum)
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGILL);
	sigprocmask(SIG_BLOCK, &set, NULL);
}

void PrintSet(sigset_t *pSet)
{
	int i = 1;
	for (; i < NSIG; ++i) {
		if (sigismember(pSet, i)) {
			putchar('1');
		}
		else {
			putchar('0');
		}
	}
	printf("\n");
}

void BlockSignal()
{
	sigset_t set01;
	sigemptyset(&set01);
	sigaddset(&set01, SIGILL);
	sigprocmask(SIG_BLOCK, &set01, NULL);
}

int main(void)
{
	sigset_t set;
	sigset_t bset;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, NULL);

	if (SIG_ERR == signal(SIGINT, IntHandler)) {
		perror("Install SIGINT error:\n");
	}

	if (SIG_ERR == signal(SIGQUIT, QuitHandler)) {
		perror("Install SIGINT error:\n");
	}

	BlockSignal();

	while (1) {
		sigpending(&bset);
		PrintSet(&bset);
		sleep(2);
	}
	return 0;
}
