/****************************************************************************
**
**  Copyright (C) 2017 liushixiongcpp@163.com
**  All rights reserved.
**
****************************************************************************/

#ifndef _share_memory_h
#define _share_memory_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#define APPLICATION_NAME "sharememory"

#define ERR_EXIT(message)   \
    do { \
        perror(message);   \
        exit(EXIT_FAILURE); \
    } while(0)


int sm_mmap();

int sm_unmmap();

#endif /* _share_memory_h */
