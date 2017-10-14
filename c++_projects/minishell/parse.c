#include "init.h"
#include "parse.h"
#include "externs.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void shell_loop(void)
{
    while (1) {
        printf("[minishell]$ ");
        fflush(stdout);
        init();
        if (read_command() == -1) {
            break;
        }	
        if (parse_command() == -1) {
            break;
        }	
        if (execute_command() == -1) {
            //TODO error message
        }	
    }
    printf("\nexit\n");
}

/*
 * 读取命令
 * 成功返回0， 失败或者读取到文件结束符(EOF)返回-1
 * */
int read_command(void)
{
    if (fgets(cmdline, MAXLINE, stdin) == NULL) {
        return -1;
    }
    return 0;
}

/*
 * 解析命令
 * 成功返回解析到命令的个数，失败返回-1
 * */
int parse_command(void)
{
    /*ls -l*/
    /*ls\0-l\0*/

    char *cp  = cmdline;
    char *avp = avline;
    int i = 0;
    while (*cp != '\0') {
        /* 去除空格 */
        while (*cp == ' ' || *cp == '\t') { //空格或者tab键
            cp++;
        }
        
        /* 如果到了行尾，跳出循环 */
        if (*cp == '\0' || *cp == '\n') {
            break;      //TODO 疑问，这样会不会整个循环跳出来了
        }
        
        cmd.args[i] = avp;

        //解析参数
        while (*cp != '\0' && *cp != ' '
                && *cp != '\t' && *cp != '\n') {
            *avp++ = *cp++;
        }
        *avp++ = '\0';
        printf("[%s]\n", cmd.args[i]);
        ++i;
    }

    return 0;
}

/*
 * 执行命令
 * 成功返回0，失败返回-1
 * */
int execute_command()
{
	//fork子进程去执行命令，否则执行完就会misishell
    pid_t pid = fork();
    if (-1 == pid) {
        ERR_EXIT("fork");
    }

    if (0 == pid) {
        execvp(cmd.args[0], cmd.args);
    }

	//等待子进程执行结束
    wait(NULL);
    return 0;
}
