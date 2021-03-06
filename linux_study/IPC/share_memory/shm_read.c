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


typedef struct student {
    char name[32];
    int  age;
} student;

int main(int argc, char *argv[])
{

    if (argc < 3) {
        fprintf(stderr, "Usage:%s <key> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int shmid = shmget(atoi(argv[1]), atoi(argv[2]), 0);
    if (shmid < 0) {
        ERR_EXIT("shmget");
    }

    student *p = shmat(shmid, NULL, 0);
    //strncpy(p->name, "linux", 5);
    //p->age = 20;

    printf("name:%s, age:%d\n", p->name, p->age);
    shmdt(p);
    return 0;
}
