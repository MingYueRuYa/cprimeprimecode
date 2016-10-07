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

/*
 * customer--product model
 * */

int global_count = 0;

//mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//cond
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *customer_routine(void *arg)
{
	pthread_mutex_lock(&mutex);
		while (1) {
			while (global_count == 0) {
				printf("customer %d wait.\n", (int)arg);
				pthread_cond_wait(&cond, &mutex);
				printf("customer %d wakeup.\n", (int)arg);
			}
			global_count--;
			printf("cusotmer %d custom.\n", (int)arg);
		}
	pthread_mutex_unlock(&mutex);
	sleep(1);
	pthread_exit(NULL);
}

void *product_routine(void *arg)
{
	while (1) {
		pthread_mutex_lock(&mutex);
			printf("producter %d product %d start.\n", (int)arg, global_count);
			global_count++;
			printf("producter %d product %d end.\n", (int)arg, global_count);
			pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int thread_customer_count = 10;
	printf("please enter thread customer count:");
	scanf("%d", &thread_customer_count);

	int thread_product_count = 10;
	printf("please enter thread prodecter count:");
	scanf("%d", &thread_product_count);

	pthread_t tidarr[200];

	int index = 0;
	//create customer
	for (; index < thread_customer_count; ++index) {
		pthread_create(&tidarr[index], NULL, customer_routine, (void *)index);
	}

	//create producter
	for (index = 0; index < thread_product_count; ++index) {
		pthread_create(&tidarr[index + thread_customer_count], NULL, product_routine, (void *)index);
	}

	for (index = 0; index < thread_customer_count + thread_product_count; ++index) {
		pthread_join(tidarr[index], NULL);
	}
	printf("main exited.\n");
	return 0;
}
