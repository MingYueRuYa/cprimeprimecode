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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int global_num = 10;

void *thread_routine(void *arg)
{
	int j = 0;
	pthread_mutex_lock(&mutex);
		for (; j < 2; ++j) {
			printf("threadid %u, num %d.\n", pthread_self(), global_num++);
		}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_mutex_init(&mutex, NULL);
	int num = 22; 
	int loop = 2;
	int i = 0, j = 0;
	pthread_t tidarr[22];
	for (; i < num; ++i) {
		pthread_create(&tidarr[i], NULL, thread_routine, NULL);
	}
	for (i = 0; i < num; ++i) {
		pthread_join(tidarr[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}
