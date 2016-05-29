/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef ipc_sem_h
#define ipc_sem_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#ifdef __cplusplus
	extern "C" {
#endif

#define SEMERR_BASE 100
#define SEMERR_PARAM (SEMERR_BASE + 1)
#define SEMERR_EEXIST (SEMERR_BASE + 2)

int sem_creat(int key, int *semid);

int sem_open(int key, int *semid);

int sem_setval(int semid, int val);

int sem_getval(int semid, int *val);

int sem_p(int semid);

int sem_v(int semid);

#ifdef __cplusplus
}
#endif

#endif //ipc_sem_h


