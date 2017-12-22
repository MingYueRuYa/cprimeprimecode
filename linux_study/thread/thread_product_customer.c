/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

#define CUSTOMER_COUNT 	 5
#define PRODUCTER_COUNT  1
#define BUFF_SIZE		 10

sem_t g_sem_full;
sem_t g_sem_empty;
pthread_mutex_t g_mutex;

int g_buf[BUFF_SIZE];

int in 	= 0;
int out	= 0;
int product_id	= 0;
int custom_id	= 0;

void *product(void *arg)
{
	//是否已满
	sem_wait(&g_sem_full);
	//临界区
	pthread_mutex_lock(&g_mutex);

	int i = 0;
	for (; i<BUFF_SIZE; ++i) {
		printf("%02d ", i);
		if (g_buf[i] == -1) {
			printf("%s", "NULL");
		} else {
			printf("%d", g_buf[i]);
		}
	
		if (i == in) {
			printf("\t<--produce");
		}
		printf("\n");
	}
	
	printf("begin produce product %d\n", product_id);
	g_buf[in] = product_id++;
	in = (in+1)%BUFF_SIZE;

	sleep(1);
	pthread_mutex_unlock(&g_mutex);
	//发送不为空信号量
	sem_post(&g_sem_empty);
	return NULL;
}	

void *custom(void *arg)
{
	//是否为空
	sem_wait(&g_sem_empty);
	//临界区
	pthread_mutex_lock(&g_mutex);

	int i = 0;
	for (; i<BUFF_SIZE; ++i) {
		printf("%02d ", i);
		if (g_buf[i] == -1) {
			printf("%s", "NULL");
		} else {
			printf("%d", g_buf[i]);
		}
	
		if (i == out) {
			printf("\t-->custom");
		}
		printf("\n");
	}

	custom_id = g_buf[out];
	printf("begin consume product %d\n", custom_id);
	g_buf[out] = -1;
	out = (out+1)%BUFF_SIZE;
	printf("end consume product %d\n", custom_id);
	sleep(3);
	pthread_mutex_unlock(&g_mutex);
	//发送不为满信号量
	sem_post(&g_sem_full);
	return NULL;
}	

pthread_t tid[CUSTOMER_COUNT+PRODUCTER_COUNT] = {-1};

int main(int argc, char *argv[])
{
	int i = 0;
	for (; i<BUFF_SIZE; ++i) {
		g_buf[i] = -1;
	}

	sem_init(&g_sem_full, 0, BUFF_SIZE);
	sem_init(&g_sem_empty, 0, 0);
	pthread_mutex_init(&g_mutex, NULL);

	for (i=0; i<CUSTOMER_COUNT; ++i) {
		pthread_create(&tid[i], NULL, custom, (void *)i);	
	}

	i = 0;
	for (; i<PRODUCTER_COUNT; ++i) {
		pthread_create(&tid[i+CUSTOMER_COUNT], NULL, product, (void *)i);	
	}

	i = 0;
	for (; i<CUSTOMER_COUNT+PRODUCTER_COUNT; ++i) {
		printf("%hd ", tid[i]);
	}
	printf("\n");

	i = 0;
// 	for (; i<CUSTOMER_COUNT+PRODUCTER_COUNT; ++i) {
// 		pthread_join(tid[i], NULL);
// 	}

	sleep(10);

	sem_destroy(&g_sem_empty);	
	sem_destroy(&g_sem_full);	
	pthread_mutex_destroy(&g_mutex);

	return 0;
}
