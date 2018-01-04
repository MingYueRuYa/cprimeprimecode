/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include "shmfifo.h"

typedef struct stu {
    char name[32];
    int  age;
}STU;

int main(int argc, char *argv[])
{
    shmfifo_t *fifo = shmfifo_init(1234, sizeof(STU), 3);
    shmfifo_destroy(fifo);
    return 0;
}
