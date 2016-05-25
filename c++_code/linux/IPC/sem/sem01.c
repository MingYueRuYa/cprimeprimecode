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

union semun {
	int              val; 
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
								(Linux-specific) */
};

int sem_create(key_t key)
{
	int semid = semget(0x1111, 1, 0666 | IPC_CREAT | IPC_EXCL);
	if (semid < 0) {
		perror("semget error");
		if (errno == EEXIST) {
			printf("check sem is already exist.\n");
			return -1;
		}
	}
	return semid;
}

int sem_open(key_t key)
{
	int semid = semget(0x1111, 1, 0666);
	if (semid < 0) {
		perror("semget error");
		return -1;
	}
	return semid;
}

int sem_setval(int semid, int value)
{
	int ret = 0;
	union semun su;
	su.val = value;
	//second parameter is like array index.
	ret = semctl(semid, 0, SETVAL, su);
	return ret;
}

int sem_getval(int semid, int *value)
{
	int ret = 0;
	union semun su;
	//second parameter is like array index.
	ret = semctl(semid, 0, GETVAL, su);
	*value = su.val;
	printf("value %d.\n", su.val);
	return ret;
}

int sem_p(int semid)
{
	int ret = 0;
	struct sembuf buf = {0, -1, 0};
	ret = semop(semid, &buf, 1);
	return ret;
}

int sem_v(int semid)
{
	int ret = 0;
	struct sembuf buf = {0, 1, 0};
	ret = semop(semid, &buf, 1);
	return ret;
}

int main(int argc, char *argv[])
{
	//int semid = sem_create(0x1111);
	int semid = sem_open(0x1111);
	if (semid < 0) {
		perror("sem_open error");
		return -1;
	}
	int ret = 0;
	ret = sem_setval(semid, 1);
	if (ret < 0) {
		perror("sem_setval error");
		return -1;
	}
	int val = 0;
	ret = sem_getval(semid, &val);
	if (ret < 0) {
		perror("sem_getval error");
		return -1;
	}
//	printf("val is %d.\n", val);

	fork();

	if ((ret = sem_p(semid)) < 0) {
		perror("sem_p error");
		return -1;
	}
	int i = 0;
	printf("i %d, pid %d.\n", ++i, getpid());
	sleep(3);
	printf("i %d, pid %d.\n", ++i, getpid());
//	printf("pid %d, p - v.\n", getpid());
//	ret = sem_getval(semid, &val);
//	printf("val is %d.\n", val);
	
	if ((ret = sem_v(semid)) < 0) {
		perror("sem_p error");
		return -1;
	}

	ret = sem_getval(semid, &val);
//	printf("val is %d.\n", val);
	return ret;
}
