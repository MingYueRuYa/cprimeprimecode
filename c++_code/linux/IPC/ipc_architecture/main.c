/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/wait.h>

#include "ipc_shm.h"
#include "ipc_sem.h"

int g_key = 0x3333;

int TestFunc(int loopnum)
{
	printf("loopnum:%d.\n", loopnum);
	int ncount = 0;
	int ret = 0;
	int shmhdl = 0;
	int *addr = NULL;

	int semid = 0;
	sem_open(g_key, &semid);

	sem_p(semid);//临界区开始
		printf("start enter critical section, pid %d.\n", getpid());
		ret = IPC_CreateShm(".", 0, &shmhdl);
		ret = IPC_MapShm(shmhdl, (void **)&addr);
		if (NULL == addr) {
			printf("addr %0X.\n", addr);
			return -1;
		}
		*((int *)addr) = *((int *)addr) + 1;
		ncount = *((int *)addr);
		printf("ncount:%d.\n", ncount);
		ret = IPC_UnMapShm(addr);
		sleep(2);
		printf("end critical section, pid %d.\n", getpid());
	sem_v(semid);//临界区结束
	printf("process normal exit, pid %d.\n", getpid());
	return ret;
}

int main(int argc, char *argv[])
{
	int procnum = 10;
	int loopnum = 100;
	int i = 0, j = 0;
	printf("please enter child process number:\n");
	scanf("%d", &procnum);
	printf("please enter child process test number:\n");
	scanf("%d", &loopnum);
	//create shm
	int ret = 0;
	int shmhdl = 0;
	ret = IPC_CreateShm(".", sizeof(int), &shmhdl);
	if (ret != 0) {
		printf("fun IPC_CreatShm() error:%d.\n", ret);
		return ret;
	}

	//create sem
	int semid = 0;
	ret = sem_creat(g_key, &semid);
	if (ret != 0) {
		if (ret == SEMERR_EEXIST) {
			ret = sem_open(g_key, &semid);
			if (ret != 0) {
				printf("fun sem_open() error, %d.\n", ret);
				return ret;
			}
		}
		else {
			return ret;
		}
	}
	int val = 0;
	ret = sem_getval(semid, &val);
	if (ret != 0) {
		printf("func sem_getval() err:%d.\n", ret);
		return ret;
	}
	printf("sem val is %d.\n", val);
	pid_t pid;
	for (i = 0; i < procnum; i++) {
		pid = fork();
		if (pid == 0) {
			for (j = 0; j < loopnum; ++j) {
				TestFunc(loopnum);
			}
			exit(0);
		}
	}
	int childpid = 0;
	while ((childpid = waitpid(-1, NULL, 0)) > 0) {
		;
	}
	printf("parent process exit.\n");
	return 0;
}
