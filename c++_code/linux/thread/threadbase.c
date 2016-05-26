/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
//进程		和		线程
//fork				pthread_creat
//pid getpid()		tid pthread_self
//pcb				tcb
//僵尸进程			僵尸线程
//结束exit(0)		自杀 pthread_exit() 他杀pthread_cancel()

//线程从现象来说，依赖于进程生命周期，和进程不一样
//线程函数
//
//程序，放在磁盘上，静态数据一堆指令的集合 数据+指令
//linux 内核通过pcb来控制进程，有了进程内核可以管理资源，进程是竞争资源的最小单位
//线程，程序执行的最小单元。。。线程体，就是一个函数调用

//从数据共享，内存四区的角度理解线程
//线程可以使用进程的全局变量
//抛砖1：如何从进程里面往线程中数据
//	 	 如何从线程中传递出来
//方法1：全局变量，指针
//

int g_num = 0;

void *thread_routine(void *arg)
{
	int i = 0;
	printf("g_num:%d.\n", g_num);
	printf("this is thread...\n");
	for (; i < 20; i++) {
		printf("B");
		fflush(stdout);
	}
}

int main(int argc, char *argv[])
{
	int i = 0;
	printf("hello...\n");
	pthread_t tid;
	g_num = 11;
	pthread_create(&tid, NULL, thread_routine, NULL);
	for (; i < 20; ++i) {
		printf("B");
		fflush(stdout);
	}
	//sleep(1);
	pthread_join(tid, NULL); //等待线程结束
	//pthread_cancel(tid); //杀掉线程
	return 0;
}
