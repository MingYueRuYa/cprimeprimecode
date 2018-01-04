/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#ifndef _common_h
#define _common_h

#define ERR_EXIT(message)    \
    do{ \
        perror(message);    \
        exit(EXIT_FAILURE); \
    } while(0)

#endif //_common_h

