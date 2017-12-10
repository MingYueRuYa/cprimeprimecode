/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

/*
 * 哲学家就餐问题
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define DELAY (rand() % 5 + 1)

int semid = 0;

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

void wait_for_2fork(int no)
{
    int left    = no;    
    int right   = (no+1)%5;
    struct sembuf buf[2] = {{left, -1, 0}, {right, -1, 0}};
    semop(semid, buf, 2);
}

void wait_for_1fork(int no)
{
    int left    = no;    
    struct sembuf buf[1] = {left, -1, 0};
    semop(semid, buf, 1);
}

void free_2fork(int no)
{
    int left    = no;    
    int right   = (no+1)%5;
    struct sembuf buf[2] = {{left, 1, 0}, {right, 1, 0}};
    semop(semid, buf, 2);
}

void philosopher(int no)
{
    srand(getpid());
    for (;;) {
        printf("%d is thinking\n", no);
        sleep(DELAY);
        printf("%d is hungry\n", no);
        // 将获取两个资源变为原子操作
        wait_for_2fork(no);
        printf("%d is eating\n", no);
        // 将释放两个资源变为原子操作
        free_2fork(no);

        /*
        // 这种方式会造成死锁
        printf("%d is thinking\n", no);
        sleep(DELAY);
        printf("%d is hungry\n", no);
        // 将获取两个资源变为原子操作
        int right = (no+1) % 5 + 1;
        wait_for_1fork(no);
        wait_for_1fork(right);
        printf("%d is eating\n", no);
        // 将释放两个资源变为原子操作
        free_2fork(no);
        */
    }
}

int main(int argc, char *argv[])
{
    semid = semget(IPC_PRIVATE, 5, IPC_CREAT | 0666);
    if (semid == -1) {
        ERR_EXIT("semget");
    }

    union semun su;
    su.val = 1;
    for (int i=0; i<5; ++i) {
        semctl(semid, i, SETVAL, su);
    }

    int no = 0;
    pid_t pid = 0;
    for (int i=1; i<5; ++i) {
        pid = fork();
        if (pid == -1) {
            ERR_EXIT("fork");
        }

        if (pid == 0) { // child process
            no = i;
            break;
        }
    }

    philosopher(no);

    return 0;
}
