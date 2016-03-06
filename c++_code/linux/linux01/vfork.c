/*
 * vfork 不会copy父进程的数据段内容的，而是进行共享的
 * vfork执行完之后必须执行exit()或者execve()，否则程序会down掉
 * */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
	printf("this pid is %d.\n", getpid());
	char const *envp[] = {"a=c", "d=b", NULL};
	//调用execle时，替换进程印象但是pid没有被替换
	execle("./hello", NULL, envp);
	return 0;
}

int main01(void)
{
	pid_t pid;
	pid = vfork();
	if (-1 == pid) {
		perror("vfork error:");
		return -1;
	}
	if (pid > 0) {
		printf("parent pid is %d\n", getpid());
	}
	if (0 == pid) {
		printf("child process pid is %d, parent pid is %d.\n", getpid(), getppid());	
		char * const parameter[] = {"ls", "-l", NULL};
		execve("/bin/ls", parameter, NULL);
		exit(0);
	}
	return 0;
}
