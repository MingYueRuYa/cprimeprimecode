/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include "shmfifo.h"

#include <string.h>
#include <stdio.h>

typedef struct stu {
    char name[32];
    int  age;
}STU;

int main(int argc, char *argv[])
{
    shmfifo_t *fifo = shmfifo_init(1234, sizeof(STU), 3);

    STU stu;
    memset(&stu, 0, sizeof(stu));
    int i=0;
    for (; i<5; ++i) {
        shmfifo_get(fifo, (char *)&stu);
        printf("name=%s, age=%d\n", stu.name, stu.age);
        memset(&stu, 0, sizeof(stu));
    }


    return 0;
}
