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
	printf("child handler pid is %d, val %d.\n", getpid(), info->si_int);	
	union sigval val;
	val.sival_int = info->si_int;
	sigqueue(getppid(), SIGINT, val);
}

void ParentHandler(int signum, siginfo_t *info, void *p)
{
	printf("parent handler is %d, val %d.\n", getpid(), info->si_int);	
}

//all child process was create by parent.
int main(void)
{
	pid_t pid;
	pid_t pidarr[2] = {0};
	int i = 0;
	pid = fork();
	//child
	if (0 == pid) {
		pidarr[0] = getpid();
	}
	//parent
	if (pid > 0) {
		pidarr[0] = pid; //first process pid
		pid = fork();
		if (0 == pid) {
			pidarr[1] = getpid();
		}
		else if (pid > 0) {
			struct sigaction action;
			action.sa_flags = SA_SIGINFO;
			action.sa_sigaction = ParentHandler;
			sigaction(SIGINT, &action, NULL);	
		}
	}
	printf("pid %d, pid1 %d, pid2 %d.\n", getpid(), pidarr[0], pidarr[1]);
	if (pidarr[1] == getpid()) {
		printf("first process %d.\n", getpid());
		sleep(2);
		union sigval val;
		val.sival_int = pidarr[1] * 2;
		sigqueue(pidarr[0], SIGINT, val);	
		printf("sigqueue pid is %d, val is %d.\n", pidarr[1], val.sival_int);
		exit(0);
	}
	if (pidarr[0] == getpid()) {
		printf("second process pid is %d.\n", pidarr[0]);
		struct sigaction action;
		action.sa_flags = SA_SIGINFO;
		action.sa_sigaction = ChildHandler;
		sigaction(SIGINT, &action, NULL);	
		sleep(3);
		exit(0);
	}
	int status = 0;
	while (-1 != wait(&status)) {

	}
	return 0;
}
