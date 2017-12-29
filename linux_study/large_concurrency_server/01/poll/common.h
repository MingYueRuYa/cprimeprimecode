#ifndef common_h
#define common_h

#include <errno.h>
#include <stdio.h>

#define ERR_EXIT(msg)   \
    do  \
    {   \
        perror(msg);    \
        exit(EXIT_FAILURE);  \
    } while (0)

#endif //common_h
