/*
 * about sigprocmask sigpendding function
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void SigquitHandler(int pSignum)
{
	printf("caught sigquit.\n");
	if (SIG_ERR == signal(SIGQUIT, SIG_DFL)) {
		printf("Can't reset sigquit");
	}
	return;
}

int main(void)
{
	sigset_t newmask, oldmask, pendmask;
	if (SIG_ERR == signal(SIGQUIT, SigquitHandler)) {
		printf("instll sigquit error.\n");
		exit(-1);	
	}
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	if (-1 == sigprocmask(SIG_BLOCK, &newmask, &oldmask)) {
		printf("sigprocmask error.\n");
		exit(-1);
	}
	sleep(5);

	if (-1 == sigpending(&pendmask)) {
		printf("sigpending error.\n");
		exit(-1);
	}
	if (sigismember(&pendmask, SIGQUIT)) {
		printf("pending sigquit signal.\n");
	}
	if (-1 == sigprocmask(SIG_SETMASK, &oldmask, NULL)) {
		printf("sigprocmask error.\n");
		exit(-1);
	}
	printf("sigquit unblock.\n");
	sleep(5);
	return 0;
}
