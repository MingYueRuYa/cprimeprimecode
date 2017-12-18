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

#include "common.h"

/*
int mq_getattr(mqd_t mqdes, struct mq_attr *attr);

int mq_setattr(mqd_t mqdes, const struct mq_attr *newattr,
                          struct mq_attr *oldattr);
*/

//struct mq_attr {
//long mq_flags;       /* Flags: 0 or O_NONBLOCK */
//long mq_maxmsg;      /* Max. # of messages on queue */
//long mq_msgsize;     /* Max. message size (bytes) */
//long mq_curmsgs;     /* # of messages currently in queue */
//};

int main(int argc, char *argv[])
{
    // 编译时需要连接runtime库 -lrt
    mqd_t mqid = mq_open("/abc", O_CREAT | O_RDWR, 0666, NULL);
    if (mqid == (mqd_t)-1) {
        ERR_EXIT("mq_open");
    }
    printf("open successful\n");

    struct mq_attr attr;
    if (mq_getattr(mqid, &attr) == 1) {
        ERR_EXIT("mq_getattr");
    }
    printf("#max_msg=%ld, #max_bytes=%ld, #current_on_queue=%ld\n"
            , attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    return 0;
}
