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

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "ipc_sem.h"

union semun {
	int 			val;
	struct semid_ds *buf;
	unsigned short 	*array;
	struct seminfo 	*__buf;
};

int sem_creat(int key, int *semid)
{
	int ret = 0;
	if (NULL == semid) {
		ret = SEMERR_PARAM;
		return ret;
	}
	ret = semget(key, 1, 0666 | IPC_CREAT);
	if (ret < 0) {
		ret = errno;
		if (errno == EEXIST) {
			ret = SEMERR_EEXIST;
			printf("file %s,line %d, func sem_create check sem already exist.\n", __FILE__, __LINE__);
			return ret;
		}
	}
	*semid = ret;
	ret = sem_setval(*semid, 1);
	if (ret < 0) {
		printf("func sem_setval() err:%d.\n", ret);
		return ret;
	}
	ret = 0;
	return ret;
}

int sem_open(int key, int *semid)
{
	int ret = 0;
	if (NULL == semid) {
		ret = SEMERR_PARAM;
		return ret;
	}
	ret = semget(key, 1, 0666);
	if (ret < 0) {
		printf("func sem_open error, %d.\n", ret);
		return ret;
	}
	*semid = ret;
	ret = 0;
	return 0;
}

int sem_setval(int semid, int val)
{
	int ret = 0;
	union semun su;
	su.val = val;
	ret = semctl(semid, 0, SETVAL, su);
	if (ret < 0) {
		printf("func sem_setval() error, %d.\n", ret);
		return ret;
	}
	return ret;
}

int sem_getval(int semid, int *myval)
{
	int ret = 0;
	//union semun sm;
	//if semclt cmd is GETVAL, then return value is semval.
	//ret = semctl(semid, 0, GETVAL, sm);
	ret = semctl(semid, 0, GETVAL);
	if (ret < 0) {
		printf("func sem_getval() error, %d.\n", ret);
		return ret;
	}
	*myval = ret;
	ret = 0;
	return 0;
}

//信号量p操作的时候，需要传递好几个信息给linux内核
//所以linux内核定义了一个结构
//我需要的操作信号量的下标 0
//我需要执行什么操作 1 -1
//我按照什么动作执行操作 0 UNDO NOWAITING
int sem_p(int semid)
{
	struct sembuf buf = {0, -1, SEM_UNDO};
	int ret = 0;
	ret = semop(semid, &buf, 1);
	if (ret < 0) {
		printf("flie %s, line %d, func sem_p() error, %d.\n", __FILE__, __LINE__, ret);
		return ret;
	}
	return ret;
}

int sem_v(int semid)
{
	struct sembuf buf = {0, 1, SEM_UNDO};
	int ret = 0;
	ret = semop(semid, &buf, 1);
	if (ret < 0) {
		printf("flie %s, line %d, func sem_v() error, %d.\n", __FILE__, __LINE__, ret);
		return ret;
	}
	return ret;
}


