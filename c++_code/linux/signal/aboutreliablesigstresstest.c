/*
 * signle stress test
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void IntHandler(int signum, siginfo_t * siginfo, void *pVoid)
{
	//printf("count %d.\n", siginfo->si_value.sival_int);
	printf("sig is %d.\n", signum);
}

void Handler(int num)
{
	printf("sig is %d.\n", num);
}

int main(void)
{
	//signal(SIGINT, IntHandler);
	//signal(SIGUSR1, IntHandler);
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &set, NULL);
	
	struct sigaction action;
	//action.sa_sigaction = IntHandler;
	action.sa_handler = Handler;
	action.sa_flags = SA_SIGINFO;
	if ( 0 != sigaction(SIGRTMIN, &action, NULL)) {
			perror("sigqueue error:\n");
	}
	union sigval si;
	si.sival_int = 0;
	int i = 0;
	for (; ;) {
		//sigqueue(getpid(), SIGINT, si);
		//printf("sigqueue.");
		si.sival_int += 1;
		//int ret = sigqueue(getpid(), SIGRTMIN, si);
		//printf("ret is %d.\n", ret);
		if ( 0 != sigqueue(getpid(), SIGRTMIN, si)) {
			printf("%d.\n", si.sival_int);
			perror("sigqueue error:\n");
			return -1;
		}
		//printf("sigqueue...");
	}

	for (;;) {

	}

	return 0;
}
