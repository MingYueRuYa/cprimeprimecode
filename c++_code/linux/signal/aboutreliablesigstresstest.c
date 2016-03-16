/*
 * 关于可靠和不可靠信号的压力测试
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


void IntHandler(int signum)
{
	static int count = 0;
	printf("count %d.\n", ++count);
}

int main(void)
{
	signal(SIGINT, IntHandler);
	signal(SIGUSR1, IntHandler);
	
	union sigval si;
	si.sival_int = 1;
	int i = 0;
	for (; ; ) {
		//sigqueue(getpid(), SIGINT, si);
		sigqueue(getpid(), SIGUSR1, si);
	}

	return 0;
}
