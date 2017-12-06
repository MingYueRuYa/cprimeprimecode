/****************************************************************************
**
**  Copyright (C) 2017 liushixiongcpp@163.com
**  All rights reserved.
**
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define ERR_EXIT(message)   \
    do { \
        perror(message);   \
        exit(EXIT_FAILURE); \
    } while(0)

int main(int argc, char *argv[])
{

    if (argc < 3) {
        fprintf(stderr, "Usage:%s <key> <size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int shmid = shmget(atoi(argv[1]), atoi(argv[2]), IPC_CREAT | 0666);
    if (shmid < 0) {
        ERR_EXIT("shmget");
    }
    return 0;
}
