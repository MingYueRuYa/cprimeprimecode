/*
 *	一个多线程程序里fork造成死锁的例子
 *	父进程在创建了一个线程，并对mutex加锁
 *	父进程创建了一个子进程，在子进程中调用doit，由于子进程会复制父进程的内存
 *	，这时候mutex处于锁的状态。
 *	父进程在复制子进程的时候，只会复制当前线程的执行状态，其他线程不会复制
 *	，因此子进程会处于死锁的状态
 * */


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
	return 0;
}
