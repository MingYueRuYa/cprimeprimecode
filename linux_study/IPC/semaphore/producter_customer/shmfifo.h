/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#ifndef _shmfifo_h
#define _shmfifo_h

#include "ipc.h"

typedef struct shmfifo shmfifo_t;
typedef struct shmhead shmhead_t;

struct shmhead {
    unsigned int blksize;
    unsigned int blocks;
    unsigned int rd_index;
    unsigned int wr_index;
};

struct shmfifo {
    shmhead_t *p_shm;   // 共享内存头部指针
    char *p_playload;   // 有效负载的起始地址

    int shmid;          // 共享内存ID
    int sem_mutex;      // 用来互斥用的信号量
    int sem_full;       // 用来控制共享内存是否满
    int sem_empty;      // 用来控制共享内存是否空
};

shmfifo_t *shmfifo_init(int key, int blksize, int blocks);
void shmfifo_put(shmfifo_t *fifo, const void *buf);
void shmfifo_get(shmfifo_t *fifo, char *buf);
void shmfifo_destroy(shmfifo_t *fifo);

#endif /* _shmfifo_h */
