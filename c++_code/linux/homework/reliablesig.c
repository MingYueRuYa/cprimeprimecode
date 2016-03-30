/*
 * reliable signal
 * child 1 send signal to child 2, child 2 send to parent and parent print extra info.
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>

//int sigaction(int signum, const struct sigaction *act,
//		                     struct sigaction *oldact);
void ChildHandler(int signum, siginfo_t *info, void *p)
{
	printf("pid is %d, val %d.\n", getpid(), info->si_int);	
	union sigval val;
	val.sival_int = info->si_int;
	sigqueue(getppid(), SIGINT, val);
}

void ParentHandler(int signum, siginfo_t *info, void *p)
{
	printf("pid is %d, val %d.\n", getpid(), info->si_int);	
}

int main(void)
{
	pid_t pid[2] = {0};
	int i = 0;
	pid[0] = fork();
	//child
	if (0 == pid[0]) {
		
	}
	//parent
	if (pid[0] > 0) {
			
	}
	for (; i < 2; ++i) {
		pid[i] = fork();
		if (-1 == pid[i]) {
			perror("fork error:");
			exit(-1);
		}
		if (pid[i] > 0) {
			struct sigaction action;
			action.sa_flags = SA_SIGINFO;
			action.sa_sigaction = ParentHandler;
			sigaction(SIGINT, &action, NULL);	
			break;
		}
	}
	printf("pid %d, pid1 %d, pid2 %d.\n", getpid(), pid[0], pid[1]);
	if (pid[0] == getpid()) {
		printf("first process %d.\n", getpid());
		union sigval val;
		val.sival_int = pid[0] * 2;
		sigqueue(pid[1], SIGINT, val);	
		printf("sigqueue pid is %d, val is %d.\n", pid[0], val.sival_int);
		while (1) {

		}
		//exit(0);
	}
	if (pid[1] == getpid()) {
		struct sigaction action;
		action.sa_flags = SA_SIGINFO;
		action.sa_sigaction = ChildHandler;
		sigaction(SIGINT, &action, NULL);	
		sleep(3);
		//exit(0);

		while (1) {

		}
	}
	int status = 0;
	while (-1 != wait(&status)) {

	}
	return 0;
}
