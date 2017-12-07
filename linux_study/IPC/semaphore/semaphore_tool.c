/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

#define ERR_EXIT(message)   \
    do {    \
        perror(message);    \
        exit(EXIT_FAILURE); \
    } while(0)

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
    struct sembuf sb = {0, -1, 0};
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

void usage()
{
    fprintf(stderr, "semtool -c create\n");
    fprintf(stderr, "semtool -d delete\n");
    fprintf(stderr, "semtool -p p operator\n");
    fprintf(stderr, "semtool -v v operator\n");
    fprintf(stderr, "semtool -s value set value\n");
    fprintf(stderr, "semtool -g get value\n");
    fprintf(stderr, "semtool -f get mode\n");
    fprintf(stderr, "semtool -m mode set mode\n");
}

int main(int argc, char *argv[])
{
    int opt = getopt(argc, argv, "cdpvs:gfm:");

    if (opt == '?') {
        exit(EXIT_FAILURE);
    }

    if (opt == -1) {
        usage();
        exit(EXIT_FAILURE);
    }

    key_t key = ftok(".", 's');
    int semid;
    switch(opt) {
        case 'c':
            sem_create(key);
            break;
        case 'd':
            semid = sem_create(key);
            sem_del(semid);
            break;
        case 'p':
            semid = sem_open(key);
            sem_p(semid);
            sem_getval(semid);
            break;
        case 'v':
            semid = sem_open(key);
            sem_v(semid);
            sem_getval(semid);
            break;
        case 's':
            semid = sem_open(key);
            if (NULL != optarg) {
                sem_setval(semid, atoi(optarg));
            }
            break;
        case 'g':
            semid = sem_open(key);
            sem_getval(semid);
            break;
        case 'f':
            semid = sem_open(key);
            sem_getmode(semid);
            break;
        case 'm':
            semid = sem_open(key);
            if (NULL != optarg) {
                sem_setmode(semid, optarg);
            }
            break;
        defalut:
            break;
    }

    return 0;
}
