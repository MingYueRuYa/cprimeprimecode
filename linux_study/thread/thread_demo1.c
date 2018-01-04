/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct EXIT_INFO {
    char *info;
    int flag;
}exit_info;

void *thread_routine(void *arg)
{
    int i=0;
    for (; i<20; ++i) {
        printf("B");
        fflush(stdout);
        usleep(20);
    }

    exit_info *info = (exit_info *)malloc(sizeof(exit_info));
    info->info = (char *)malloc(12);
    strcpy(info->info, "liushixiong");
    info->flag = 0;
    pthread_exit(info);
    // return "abc";
    // thread_exit("abc");
    return 0;
}

int main(int argc, char *argv[])
{
    pthread_t pid;
    int ret = pthread_create(&pid, NULL, thread_routine, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create:%s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    int i=0;
    for (; i<20; ++i) {
        printf("A");
        fflush(stdout);
        usleep(20);
    }

    exit_info *value;
    ret = pthread_join(pid, (void *)&value);
    if (ret != 0) {
        fprintf(stderr, "pthread_join:%s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    printf("info:%s, flag:%d", value->info, value->flag);

    free(value->info);
    value->info = NULL;

    free(value);
    value = NULL;

    printf("\n");
    return 0;
}
