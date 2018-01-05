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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *arg)
{
	printf("pid = %d begin doit...\n", static_cast<int>(getpid()));
	pthread_mutex_lock(&mutex);
	struct timespec ts = {2, 0};
	nanosleep(&ts, NULL);
	pthread_mutex_unlock(&mutex);
	printf("pid = %d end doit...\n", static_cast<int>(getpid()));
	return NULL;
}

int main(int argc, char *argv[])
{
	printf("pid = %d Entering main...\n", static_cast<int>(getpid()));

	pthread_t tid;
	pthread_create(&tid, NULL, doit, NULL);
	struct timespec ts = {1, 0};
	nanosleep(&ts, NULL);	

	if (fork() == 0) {
		doit(NULL);
	}

	pthread_join(tid, NULL);
	printf("pid = %d Eixting main...\n", static_cast<int>(getpid()));

	return 0;
}
