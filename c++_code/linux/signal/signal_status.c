/*
 * 信号的阻塞和未决状态
 * 注意0-31为不可靠信号
 * 信号的阻塞状态，并不是刚开始设置的时候就能看到的，而是先设置了，当有信号到达时，才能在未决状态的时候看到 
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define ERR_EXIT(num) \
		do {  \
			perror(num); \
			exit(EXIT_FAILURE);	 \
		} while(0) 

void Handler(int pSignum)
{
	printf("Handler.\n");
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	printf("Handler...");
	PrintSigset(&set);
	printf("Handler...");
	if (-1 == sigprocmask(SIG_BLOCK, &set, NULL)) {
		ERR_EXIT("sigprocmask error:");
	}
//	if (pSignum == SIGINT) {
//		printf("Recive SIGINT is %d.\n", pSignum);
//	}
//	else if (pSignum == SIGQUIT) {
//		sigset_t set;
//		sigemptyset(&set);
//		sigaddset(&set, SIGINT);
//		if (-1 == sigprocmask(SIG_UNBLOCK, &set, NULL)) {
//			ERR_EXIT("sigprocmask error:");
//		}
//	}
}

void PrintSigset(sigset_t *pSet)
{
	int i = 0;
	for (i = 1; i < NSIG; ++i) {
		if (sigismember(pSet, i)) {
			putchar('1');
		} else {
			putchar('0');
		}
	}
	printf("\n");
}

void UnBlockQuit(int signum)
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	if (-1 == sigprocmask(SIG_UNBLOCK, &set, NULL)) {
		perror("sigprocmask error:\n");
	}
	//PrintSigset(&set);	
}

int main(void)
{
	sigset_t set;	
//	if (SIG_ERR == signal(SIGQUIT, Handler)) {
//		perror("Install SIGQUIT error:\n");
//	}

	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	sigprocmask(SIG_BLOCK, &set, NULL);
//
	if (SIG_ERR == signal(SIGINT, UnBlockQuit)) {
		perror("Install SIGINT error:\n");
	}

	if (SIG_ERR == signal(SIGQUIT, Handler)) {
		perror("Install SIGINT error:\n");
	}
//	sigemptyset(&set);
//	sigaddset(&set, SIGINT);
//	sigprocmask(SIG_BLOCK, &set, NULL);

	for ( ; ;) {
		sigpending(&set);
		PrintSigset(&set);
		sleep(2);
	}

	return 0;
}

//打印未决状态
int main_print_pending(void)
{
	sigset_t set;
	
	while (1) {
		sigpending(&set);
		PrintSigset(&set);
		sleep(2);
	}

	return 0;
}
