/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#ifndef _ipc_h
#define _ipc_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define ERR_EXIT(message)   \
    do {    \
        perror(message);    \
        exit(EXIT_FAILURE); \
    } while(0)

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

int sem_create(key_t key);
int sem_open(key_t key);
int sem_setval(const int semid, const int value);
int sem_getval(const int semid);
int sem_del(const int semid);
int sem_p(const int semid);
int sem_v(const int semid);
int sem_getmode(const int semid);
int sem_setmode(const int semid, const char *mode);

#endif /* _ipc_h */
