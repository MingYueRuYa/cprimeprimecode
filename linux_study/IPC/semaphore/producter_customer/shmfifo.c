/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include "shmfifo.h"

#include <assert.h>
#include <string.h>

#include <sys/shm.h>

shmfifo_t *shmfifo_init(int key, int blksize, int blocks)
{
    shmfifo_t *fifo = (shmfifo_t *)malloc(sizeof(shmfifo_t));
    assert(fifo != NULL);
    memset(fifo, 0, sizeof(shmfifo_t));

    int shmid = shmget(key, 0, 0);  //假设已存在，用原有的权限打开
    int size = sizeof(shmhead_t) + blksize * blocks;
    if (-1 == shmid) {
        fifo->shmid = shmget(key, size, IPC_CREAT | 0666);
        if (-1 == fifo->shmid) {
            ERR_EXIT("shmget");
        }
        fifo->p_shm = (shmhead_t *)shmat(fifo->shmid, NULL, 0);
        if ((shmhead_t *)-1 == fifo->p_shm) {
            ERR_EXIT("shmat");
        }

        fifo->p_playload        = (char *)(fifo->p_shm+1);
        fifo->p_shm->rd_index   = 0;
        fifo->p_shm->wr_index   = 0;
        fifo->p_shm->blocks     = blocks;
        fifo->p_shm->blksize    = blksize;
        
        fifo->sem_mutex = sem_create(key);
        fifo->sem_full  = sem_create(key+1);
        fifo->sem_empty = sem_create(key+2);

        sem_setval(fifo->sem_mutex, 1);
        sem_setval(fifo->sem_full, blocks);
        sem_setval(fifo->sem_empty, 0);
    } else {
        fifo->shmid = shmid;
        fifo->p_shm = (shmhead_t *)shmat(fifo->shmid, NULL, 0);
        if ((shmhead_t *)-1 == fifo->p_shm) {
            ERR_EXIT("shmat");
        }

        fifo->p_playload = (char *)(fifo->p_shm+1);
        
        fifo->sem_mutex = sem_create(key);
        fifo->sem_full  = sem_create(key+1);
        fifo->sem_empty = sem_create(key+2);
    }
    return fifo;
}

void shmfifo_put(shmfifo_t *fifo, const void *buf)
{
    sem_p(fifo->sem_full);
    sem_p(fifo->sem_mutex);

    memcpy(fifo->p_playload+fifo->p_shm->blksize*fifo->p_shm->wr_index
            , buf, fifo->p_shm->blksize);
    fifo->p_shm->wr_index = (fifo->p_shm->wr_index+1)%fifo->p_shm->blocks;

    sem_v(fifo->sem_mutex);
    sem_v(fifo->sem_empty);
}

void shmfifo_get(shmfifo_t *fifo, char *buf)
{
    sem_p(fifo->sem_empty);
    sem_p(fifo->sem_mutex);
    
    memcpy(buf, fifo->p_playload+fifo->p_shm->blksize*fifo->p_shm->rd_index
            , fifo->p_shm->blksize);
    fifo->p_shm->rd_index = (fifo->p_shm->rd_index+1)%fifo->p_shm->blocks;

    sem_v(fifo->sem_mutex);
    sem_v(fifo->sem_full);
}

void shmfifo_destroy(shmfifo_t *fifo)
{
    sem_del(fifo->sem_mutex);
    sem_del(fifo->sem_full);
    sem_del(fifo->sem_empty);

    shmdt((void *)fifo->p_shm);
    shmctl(fifo->shmid, IPC_RMID, 0);
    free(fifo);
    fifo = NULL;
}
