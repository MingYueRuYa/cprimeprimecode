/*
 * 父进程和子进程的文件描述符
 * 实验结论：
 * 		父进程和子进程会同时现文件中写入数据的，但是先后顺序不能确定的。
 * 		在fork之后，子进程的会copy父进程的fd(fd本质就是一个指针指向同一个文件，两个进程共用一个文件位置偏移量，但是文件的referencecount = 2, 这样的话，在关闭文件描述符的时候需要关闭两次，referencecount才能为0。同时记住，父进程和子进程是从两个地址空间现fd文件中写入数据，文件系统的管理是由vfs管理)
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
	int fd;
	fd = open("./1.txt", O_RDWR);	
	if (-1 == fd) {
		perror("Open error:");
		return -1;
	}
	pid = fork();
	if (-1 == pid) {
		perror("fork error:");
		return -1;
	}
	if (pid > 0) {
		write(fd,"parent", 6);
		close(fd);
	}
	if (0 == pid) {
		write(fd,"child", 5);
		close(fd);
		exit(0);
	}
	return 0;
}
