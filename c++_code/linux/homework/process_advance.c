/*
 * reliable signal
 * child 1 send signal to child 2, child 2 send to parent and parent print extra info.
 * */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

pid_t pidarray[10];

void SolveHandler(int pSigNum, siginfo_t *pSigInfo, void *pExtraParameter)
{
	if (SIGRTMIN + 1 == pSigNum) {
		//child 1 receive signal
		printf("child 1 receive signal, value is %d.", pSigInfo->si_value.sival_int);		
		pidarray[1] = pSigInfo->si_value.sival_int;
	}
	else if (SIGRTMIN + 2 == pSigNum) {
		//child 2 receive signal, child 1 send signal to child 2 with data is child 1 pid * 2.
		printf("child 2 receive signal, value is %d.", pSigInfo->si_value.sival_int);		
		pidarray[3] = pSigInfo->si_value.sival_int;
	}
	else if (SIGRTMIN + 3 == pSigNum) {
		//child 2 receive data send to parent
		printf("parent receive signal, value is %d.", pSigInfo->si_value.sival_int);		
		printf("parent pid[0]=%d, pid[1]=%d.\n", pidarray[0], pidarray[1]);
	}
}


int main(void)
{
	struct sigaction act;
	act.sa_sigaction = SolveHandler;
	act.sa_flags = SA_SIGINFO;
	if (-1 == sigaction(SIGRTMIN + 1, &act, NULL)) {
		perror("sigaction error:\n");
		exit(-1);	
	}
	if (-1 == sigaction(SIGRTMIN + 2, &act, NULL)) {
		perror("sigaction error:\n");
		exit(-1);	
	}
	if (-1 == sigaction(SIGRTMIN + 3, &act, NULL)) {
		perror("sigaction error:\n");
		exit(-1);	
	}
	int i = 0;
	pid_t pid;
	for (; i < 2; ++i) {
	   	pid = fork();	
		if (pid == 0) { //child process
			break;
		}
		else { //pid > 0 parent process
			//TODO todo something
			pidarray[i] = pid;
		}
	}
	if (pid > 0) { //parent
		printf("parent run...\n");
		//send child 2 pid to child 1
		union sigval val;
		val.sival_int = pidarray[1];
		sigqueue(pidarray[0], SIGRTMIN+1, val);
		while (1) {
			int status; 
			pid_t pid = wait(&status);
			if (-1 == pid) {
				if (errno == EINTR) { //interupt by singal
					continue;
				}
				return -1;
			}
		}
	}
	if (0 == pid && 0 == i) { //child 1
		sleep(10);
		union sigval val;
		val.sival_int = getpid() * 2;
		sigqueue(pidarray[1], SIGRTMIN+2, val);
		printf("child 1 already send signal.\n");
		//exit(0);
		while (1) {

		}
	}
	if (0 == pid && 1 == i) { //child 2
		sleep(10);
		printf("child 2 wakeup.\n");
		union sigval val;
		val.sival_int = pidarray[3];
		sigqueue(getppid(), SIGRTMIN+3, val);
		//exit(0);
		while (1) {

		}
	}
	return 0;
}
