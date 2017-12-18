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
    if (argc != 2) {
        fprintf(stderr, "Usage:%s <prio> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    mqd_t mqid = mq_open("/abc", O_RDWR);
    if (mqid == (mqd_t)-1) {
        ERR_EXIT("mq_open");
    }

    Student std;
    int len = strlen("liushixiong is a cpper");
    strncpy(std.name, "liushixiong is a cpper", len);
    int msg_prio = atoi(argv[1]);
    int ret = mq_send(mqid, (char *)&std, sizeof(std), msg_prio);
    if (ret == -1) {
        ERR_EXIT("mq_send");
    }

    struct mq_attr attr;
    if (mq_getattr(mqid, &attr) == 1) {
        ERR_EXIT("mq_getattr");
    }
    printf("#max_msg=%ld, #max_bytes=%ld, #current_on_queue=%ld\n"
            , attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    mq_close(mqid);
    return 0;
}
