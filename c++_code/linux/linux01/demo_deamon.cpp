/*
 * deamon后台服务进程，有以下5个步骤
 * 1.想要fork一个子进程
 * 2.父进程exit退出（父进程退出的原因：父进程是一个进程组组长，根据man手册，组长不能调用setsid()）
 * 3.新建一个session（新建一个session是为了脱离当前的tty，让程序在后台运行不依赖于任何的tty）
 * 4.修改fork子进程的目录为根目录（如果不修改为根目录的话，则当前目录是不能卸载的，如果当前目录没有用的话，应该把它卸载了）
 * 5.将标准输入、输出、错误重定向到/dev/null（如果不重定向到/dev/null下的话，deamon可能在标准输出或者其他的输出信息）
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	pid_t pid;
	int i = 0;
	pid = fork();
	if (-1 == pid) {
		perror("Fork error:");
		exit(-1);
	}
	if (pid > 0) {
		exit(0);//父进程退出
	}
	pid = setsid();
	if (-1 == pid) {
		perror("Setsid error:");
		exit(-1);
	}

	printf("child process pid is %d.\n", getpid());
	chdir("/"); //修改目录为"/"

	for (; i < 3; ++i) {
		close(i);
	}	
	open("/dev/null", O_RDWR); //关闭标注的输入和输出、错误
	dup(0); //将1号文件描述符指向0
	dup(0); //将2号文件描述符指向0
	while (1) {
		sleep(1);
	}
	return 0;
}
