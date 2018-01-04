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

#include "common.h"

typedef struct student {
    char name[32];
    int  age;
}Student;

int main(int argc, char *argv[])
{
    mqd_t mqid = mq_open("/abc", O_RDWR);
    if (mqid == (mqd_t)-1) {
        ERR_EXIT("mq_open");
    }

    struct mq_attr attr;
    if (mq_getattr(mqid, &attr) == 1) {
        ERR_EXIT("mq_getattr");
    }

    Student std;
    unsigned int msg_prio = 0;
    //取消息时，默认是按照msg_prio从大到小顺序
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

    mq_close(mqid);
    return 0;
}
