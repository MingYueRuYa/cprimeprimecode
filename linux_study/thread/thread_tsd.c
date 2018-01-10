/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

// 设置线程的私有数据

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#include "common.h"

typedef struct tsd {
    pthread_t   tid;
    char        *str;
}tsd_t;

pthread_key_t key_tsd;
pthread_once_t once_control = PTHREAD_ONCE_INIT;

void destroy_routine(void *value)
{
    printf("destroy...%p, value %p\n", 
			(unsigned int)pthread_self(), 
			(unsigned int)value);
    free(value);
    value = NULL;
}

void once_routine(void)
{
    pthread_key_create(&key_tsd, destroy_routine);
    printf("once_routine...\n");
}

void* thread_routine(void *msg)
{
    //2.只有第一个线程进来的时候创建
    pthread_once(&once_control, once_routine);

    tsd_t *value = (tsd_t *)malloc(sizeof(tsd_t));
    value->tid = pthread_self();
    value->str = (char *)msg;

    pthread_setspecific(key_tsd, value);
    printf("%s setspecific %p\n", (char *)msg, value);
    value = pthread_getspecific(key_tsd);
    printf("tid=0x%x, str=%s\n", (unsigned int)value->tid, value->str);
    sleep(2);
    value = pthread_getspecific(key_tsd);
    printf("tid=0x%x, str=%s\n", (unsigned int)value->tid, value->str);
    return NULL;
}

int main(int argc, char *argv[])
{
    // 1.创建key
    // pthread_key_create(&key_tsd, destroy_routine);

    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, thread_routine, "thread1");
    pthread_create(&t2, NULL, thread_routine, "thread2");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_key_delete(key_tsd);

	return 0;
}
