/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include "ipc.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int sem_create(key_t key)
{
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid < 0) {
        ERR_EXIT("semget");
    }
    return semid;
}

int sem_open(key_t key)
{
    int semid = semget(key, 0, 0);
    if (semid < 0) {
        ERR_EXIT("semget");
    }
    return semid;
}

int sem_setval(const int semid, const int value)
{
    union semun su;
    su.val = value;
    int ret = semctl(semid, 0, SETVAL, su);
    if (ret < 0) {
        ERR_EXIT("sem_setval");
    }
    return ret;
}

int sem_getval(const int semid)
{
    int ret = semctl(semid, 0, GETVAL, 0);
    if (ret < 0) {
        ERR_EXIT("sem_getval");
    }
    printf("value %d\n", ret);
    return ret;
}

int sem_del(const int semid)
{
    int ret = semctl(semid, 0, IPC_RMID, 0);
    if (ret < 0) {
        ERR_EXIT("sem_del");
    }
    return ret;
}

int sem_p(const int semid)
{
    // SEM_UNDO 进程退出资源自动加+1
    // IPC_NOWAIT 如果没有资源，立即退出不会阻塞，并这是errno=EAGAIN
    struct sembuf sb = {0, -1,  0 /* IPC_NOWAIT | SEM_UNO */};
    int ret = semop(semid, &sb, 1);
    if (ret < 0) {
        ERR_EXIT("sem_p");
    }
    return ret;
}

int sem_v(const int semid)
{
    struct sembuf sb = {0, 1, 0};
    int ret = semop(semid, &sb, 1);
    if (ret < 0) {
        ERR_EXIT("sem_v");
    }
    return ret;
}

int sem_getmode(const int semid)
{
    union semun su;
    struct semid_ds sem;
    su.buf = &sem;
    int ret = semctl(semid, 0, IPC_STAT, su);
    if (ret < 0) {
        ERR_EXIT("sem_getmode");
    }
    printf("current mode %ho\n", su.buf->sem_perm.mode);
    return ret;
}

int sem_setmode(const int semid, const char *mode)
{
    union semun su;
    struct semid_ds sem;
    su.buf = &sem;
    int ret = semctl(semid, 0, IPC_STAT, su);
    if (ret < 0) {
        ERR_EXIT("sem_setmode");
    }

    printf("current permissions is %o\n", su.buf->sem_perm.mode);
    sscanf(mode, "%ho", &su.buf->sem_perm.mode);
    ret = semctl(semid, 0, IPC_SET, su);
    if (ret < 0) {
        ERR_EXIT("sem_setmode");
    }
    printf("permissions updated...\n");
    return ret;
}
