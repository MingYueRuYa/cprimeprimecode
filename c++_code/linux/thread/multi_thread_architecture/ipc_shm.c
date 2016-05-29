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
#include <sys/shm.h>

#include "ipc_shm.h"

int shmflag = 0;
int shmkey;

int IPC_CreateShm(char *fileseedfile, int shmsize, int *shmhdl)
{
	if (0 == shmflag) {
		shmkey = ftok(fileseedfile, 'C');
		if (shmkey < 0) {
			perror("fotk error");
			return -1;
		}
		shmflag = 1;
	}
	*shmhdl = shmget(shmkey, shmsize, 0666 | IPC_CREAT);
	if (*shmhdl < 0) {
		return -1;
	}
	return 0;
}

int IPC_MapShm(int shmhdl, void **mapaddr)
{
	void *tmp = NULL;
	tmp = (void *)shmat(shmhdl, 0, SHM_RND);
	if (tmp < 0) {
		printf("file %s, function %s, line %d, addr %0X.\n", __FILE__, __func__, __LINE__, tmp);
		perror("shmat error");
		return -1;
	}
	*mapaddr = tmp;
	return 0;
}

int IPC_UnMapShm(void *unmapaddr)
{
	if (shmdt(unmapaddr) < 0) {
		perror("unmapaddr error");
		return -1;
	}
	return 0;
}

int IPC_DelShm(int shmhdl)
{
	if (shmctl(shmhdl, IPC_RMID, NULL) < 0) {
		perror("shmctl error");
		return -1;
	}
	return 0;
}
