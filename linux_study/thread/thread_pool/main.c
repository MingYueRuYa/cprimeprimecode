/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "thread_pool.h"

void *mytask(void *arg)
{
    printf("thread 0x%0x is working on task %d\n"
            , (int)pthread_self()
            , *(int *)arg);
    sleep(1);
    free(arg);
    return NULL;
}

int main(int argc, char *argv[])
{
    threadpool_t pool;
    threadpool_init(&pool, 3);

    int i = 0;
    for (; i<5; ++i) {
        int *index = (int *)malloc(sizeof(int));
        *index = i;
        threadpool_add_task(&pool, mytask, (void *)index);
    }
    threadpool_destroy(&pool);

    return 0;
}

