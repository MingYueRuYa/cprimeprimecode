
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

void  myhandle(int num)
{
	if (num == SIGUSR1)
	{
		//把SIGINT和SIGRTMIN均添加到本进程的阻塞状态字中
		sigset_t bset;
		sigemptyset(&bset);
		sigaddset(&bset, SIGINT);
		sigaddset(&bset, SIGRTMIN);
		
		sigprocmask(SIG_UNBLOCK, &bset, NULL);
		printf("解除阻塞 recv sig num:%d \n", num);
	}
	else if (num == SIGINT || num== SIGRTMIN)
	{	
		//printf("recv sig num:%d \n", num);
	}
	else
		{
			printf("其他recv sig num:%d \n",  num);
		}
}

void main()
{
	pid_t 	pid;
	
	struct sigaction act;
	act.sa_handler = myhandle;
	act.sa_flags = SA_SIGINFO;  //千万别忘记了

	//注册非实时信号 处理函数
	if ( sigaction(SIGINT, &act, NULL) <0 )
	{
		ERR_EXIT("sigaction SIGINT");
	}
	//注册实时信号的处理函数
	if ( sigaction(SIGRTMIN, &act, NULL) <0 )
	{
		ERR_EXIT("sigaction SIGINT");
	}
	
	//注册了一个用户自定义信号SIGUSR1 处理函数
	if ( sigaction(SIGUSR1, &act, NULL) <0 )
	{
		ERR_EXIT("sigaction SIGINT");
	}
	
	//把SIGINT和SIGRTMIN均添加到本进程的阻塞状态字中
	sigset_t bset;
	sigemptyset(&bset);
	sigaddset(&bset, SIGINT);
	//sigaddset(&bset, SIGRTMIN);
	
	sigprocmask(SIG_BLOCK, &bset, NULL);
	
	pid = fork();
	if (pid == -1)
	{
		ERR_EXIT("fork err");
	}
	
	if (pid == 0)
	{
		int i = 0;
		int ret = 0;
		 union sigval v;
		 v.sival_int = 201;

//		//发三次不稳定信号
//		for (i=0; i<3; i++)
//		{
//			ret = sigqueue(getppid(), SIGINT, v);
//			if (ret != 0)
//			{
//				printf("发送不可靠信号失败 ret: %d, errno:%d \n", ret, errno);
//				exit(0);
//			}	
//			else
//			{
//				printf("发送不可靠信号ok\n");
//			}
//		}
	
		 v.sival_int = 1;
		//发三次稳定信号
		for (i=0; i< 10 * 1024; i++)
		{
 			++v.sival_int;
			ret = sigqueue(getppid(), SIGRTMIN, v);
			if (ret != 0)
			{
				printf("发送可靠信号失败 ret: %d, errno:%d \n", ret, errno);
				exit(0);
			}	
			printf("发送可靠信号ok\n");
		}
		//kill(getppid(), SIGUSR1);
	}
	
	while(1)
	{
		sleep(1);
	}
	
	printf("main....\n");
}
