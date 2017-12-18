/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#include "common.h"

//TODO: notic
// 任何时刻只能有一个进程可以被注册为接收某一个给定队列的通知
// 此消息只能传递一次，要想每次都notify，需要重复注册

typedef struct student {
    char name[32];
    int  age;
}Student;

mqd_t mqid  = 0;

void handle_sigusr1(int signo)
{
    signal(SIGUSR1, handle_sigusr1);

    struct sigevent sevp;
    sevp.sigev_notify   = SIGEV_SIGNAL;
    sevp.sigev_signo    = SIGUSR1;
    mq_notify(mqid, &sevp);

    Student std;
    unsigned int msg_prio = 0;
    //取消息时，默认是按照msg_prio从大到小顺序
    struct mq_attr attr;
    if (mq_getattr(mqid, &attr) == 1) {
        ERR_EXIT("mq_getattr");
    }
    ssize_t ret = mq_receive(mqid , (char *)&std, attr.mq_msgsize, &msg_prio);
    if (ret == -1) {
        ERR_EXIT("mq_receive");
    }

    printf("studen name=%s,age=%d, msg priority=%d\n"
            , std.name, std.age, msg_prio);

    if (mq_getattr(mqid, &attr) == 1) {
        ERR_EXIT("mq_getattr");
    }
    printf("#max_msg=%ld, #max_bytes=%ld, #current_on_queue=%ld\n"
            , attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
}

int main(int argc, char *argv[])
{
    signal(SIGUSR1, handle_sigusr1);

    mqid = mq_open("/abc", O_RDWR);
    if (mqid == (mqd_t)-1) {
        ERR_EXIT("mq_open");
    }

    struct mq_attr attr;
    if (mq_getattr(mqid, &attr) == 1) {
        ERR_EXIT("mq_getattr");
    }

    struct sigevent sevp;
    sevp.sigev_notify   = SIGEV_SIGNAL;
    sevp.sigev_signo    = SIGUSR1;
    mq_notify(mqid, &sevp);

    for(;;) {
        pause();
    }

    mq_close(mqid);
    return 0;
}
