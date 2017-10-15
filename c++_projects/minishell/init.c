#include "init.h"
#include "externs.h"

#include <stdio.h>
#include <signal.h>
#include <string.h>

void sigint_handler(int sig);

/*
 * 安装ctrl+C信号，ctrl+/退出信号
 * */
void setup(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN); //忽略ctrl+/退出信号
}

void sigint_handler(int sig)
{
    printf("\n[minishell]$ ");
    fflush(stdout);
}

/*
 * 初始化全局变量
 * */
void init(void)
{
    memset(cmd, 0, sizeof(cmd));
    int i;
    for (i=0; i<PIPELINE; ++i) {
        cmd[i].infd  = 0;
        cmd[i].outfd = 1;
    }

    memset(cmdline, 0, sizeof(cmdline));
    memset(avline, 0, sizeof(avline));
    lineptr = cmdline;
    avptr   = avline;
    memset(infile, 0, sizeof(infile));
    memset(outfile, 0, sizeof(outfile));

    append    = 0;
    backgnd   = 0;
    cmd_count = 0;
    lastpid   = 0;

    printf("[minishell]$ ");
    fflush(stdout);
}
