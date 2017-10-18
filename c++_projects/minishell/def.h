#ifndef _DEF_H
#define _DEF_H

#include <stdio.h>
#include <stdlib.h>

#define ERR_EXIT(msg) \
    do \
    {   \
        perror(msg);    \
        exit(EXIT_FAILURE); \
    } while(0)

#define MAXLINE 1024    /* 输入行的最大长度 */
#define MAXARG  20      /* 每个简单的命令的参数最多个数 */
#define PIPELINE 5       /* 一个管道行中简单命令的最多个数 */
#define MAXNAME 100     /* IO 重定向文件名的最大长度 */

typedef struct command
{
    char *args[MAXARG+1];   /* 解析出的命令参数列表, 最后一个为NULL */
	int infd;
	int outfd;
} COMMAND;

#endif //_DEF_H
