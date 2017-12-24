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

#define CUSTOMER_COUNT 	 1
#define PRODUCTER_COUNT  5

pthread_mutex_t g_mutex;
pthread_cond_t  g_cond;

int g_product = 0;

void *product(void *arg)
{
    int index = *(int *)arg;
    while (1) {
        //临界区
        pthread_mutex_lock(&g_mutex);
        printf("%d begin create product...\n", index);
        ++g_product;
        printf("%d begin create product...\n", index);
        pthread_cond_signal(&g_cond);
        printf("%d signal..\n", index);
        pthread_mutex_unlock(&g_mutex);
        sleep(5);
    }
    free(arg);
    arg = NULL;
	return NULL;
}	

void *custom(void *arg)
{
    int index = *(int *)arg;
    while (1) {
        //临界区
        pthread_mutex_lock(&g_mutex);
        while (g_product == 0) {
            printf("%d begin wait a condition...\n", index);
            pthread_cond_wait(&g_cond, &g_mutex);
        }
        printf("%d end wait condition...\n", index);
        --g_product;
        pthread_mutex_unlock(&g_mutex);
        //是否为空，为空就等待
        sleep(1);
    }
    free(arg);
    arg = NULL;
	return NULL;
}	

int main(int argc, char *argv[])
{
    pthread_t tid[CUSTOMER_COUNT+PRODUCTER_COUNT];
    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_cond, NULL);

    int i = 0;
    for (; i<CUSTOMER_COUNT; ++i) {
        int *index = (int *)malloc(sizeof(i));
        *index = i;
        pthread_create(&tid[i], NULL, custom, (void *)index);
    }

    for (i=0; i<PRODUCTER_COUNT; ++i) {
        int *index = (int *)malloc(sizeof(i));
        *index = i;
        pthread_create(&tid[i+CUSTOMER_COUNT], NULL, product, (void *)index);
    }

    for (i=0; i<PRODUCTER_COUNT+CUSTOMER_COUNT; ++i) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_cond);
	return 0;
}
