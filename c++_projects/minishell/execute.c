#include "execute.h"
#include "def.h"
#include "externs.h"

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <fcntl.h>

void forkexec(int i)
{
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        ERR_EXIT("fork"); 
    }

    if (pid > 0) { //父进程返回，但是返回的确实子进程的ID
        /* 父进程 */
        if (backgnd == 1) {
            printf("[%d].\n", pid);
        }
        lastpid = pid;
    } else if (pid == 0) {
        //当backgnd=1时，将第一条简单命令的infd重定向至/dev/null
        //当第一条命令试图从标准输入获取数据的时候立即返回EOF
        if (cmd[i].infd == 0 && backgnd == 1) {
            cmd[i].infd = open("/dev/null", O_RDONLY);
        }

        //将第一个简单命令进程作为进程组组长
        //这样做是为了在接收ctrl+c时，当前进程组的中所有进程都能收到信号
        //所以新开一个进程组，是为了不影响主进程
        if (i == 0) {
            setpgid(0, 0);
        }

        /* 子进程 */
        if (cmd[i].infd != 0) {
            close(0);
            dup(cmd[i].infd);
        }
        if (cmd[i].outfd != 1) {
            close(1);
            dup(cmd[i].outfd);
        } //if
        int j;
        for (j=3; j<NR_OPEN; ++j) {
            close(j);
        } // for
        
        //前台作业能够接收SIGINT、SIGQUIT信号
        //这两个信号要恢复为默认操作
        if (backgnd == 0) {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
        }

        execvp(cmd[i].args[0], cmd[i].args);
        exit(EXIT_FAILURE);
    } // else if
}

/*
 * 执行命令
 * 成功返回0，失败返回-1
 * */
int execute_disk_command(void)
{
    //如果命令为空，直接返回，不做任何动作
    if (cmd_count == 0) {
        return 0;
    }

    if (infile[0] != '\0') {
        cmd[0].infd = open(infile, O_RDONLY);
    }

    if (outfile[0] != '\0') {
        if (append) {
            cmd[cmd_count-1].outfd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
        } else {
            cmd[cmd_count-1].outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        }
    }

    //因为后台进程不会调用wait等待子进程退出
    //为避免僵尸进程，可以忽略SIGCHLD信号
    if (backgnd == 1) {
        signal(SIGCHLD, SIG_IGN);
    } else {
        signal(SIGCHLD, SIG_DFL);
    }

    int i;
    int fd;
    int fds[2];
    for (i=0; i<cmd_count; ++i) {
        /* 如果不是最后一条命令，则需要创建管道 */
        if (i<cmd_count-1) {
            pipe(fds);
            cmd[i].outfd = fds[1];  //写管道
            cmd[i+1].infd = fds[0]; //读管道
        }

        forkexec(i);

        if ((fd = cmd[i].infd) != 0) {
            close(fd);
        }

        if ((fd = cmd[i].outfd) != 1) {
            close(fd);
        }
    }

    if (backgnd == 0) {
        //前台作业，需要等待管道中最后一个命令退出
        while (wait(NULL) != lastpid)  {;}
    }

    return 0;
}
