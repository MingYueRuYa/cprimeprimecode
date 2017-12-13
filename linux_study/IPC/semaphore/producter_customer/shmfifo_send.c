/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include "shmfifo.h"
#include <string.h>

typedef struct stu {
    char name[32];
    int  age;
}STU;

int main(int argc, char *argv[])
{
    shmfifo_t *fifo = shmfifo_init(1234, sizeof(STU), 3);

    STU s;
    memset(&s, 0, sizeof(STU));
    s.name[0] = 'a';
    int i=0;
    for (; i<5; i++) {
        s.name[0] = s.name[0]+1;
        s.age = i+20;
        shmfifo_put(fifo, &s);
    }
    return 0;
}
