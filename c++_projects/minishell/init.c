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
    memset(&cmd, 0, sizeof(cmd));
    memset(cmdline, 0, sizeof(cmdline));
}
