/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "childthread.h"

using namespace std;

int main01(int argc, char *argv[])
{
	ChildThread childthread;
	childthread.Start();
	childthread.Stop();

	return 0;
}


int G_COUNT = 0;
const int G_COUNT_MAX = 10;

//mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//cond
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *Customer(void *pArg)
{
	while (1) {
		pthread_mutex_lock(&mutex);
		while (0 == G_COUNT) {
			//customer blocked, notify producter
			cout << "Customer " << (long)pArg << " wait." << endl;
			pthread_cond_wait(&cond, &mutex);
		}
		G_COUNT--;
		cout << "count "<< G_COUNT << " customer " << (long)(pArg) << endl;
		if (G_COUNT_MAX - 1 == G_COUNT) {
			pthread_cond_signal(&cond);
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_exit(0);
	return NULL;
}

void *Producter(void *pArg)
{
	while (1) {
		pthread_mutex_lock(&mutex);
		while (G_COUNT_MAX == G_COUNT) {
			//producter blocked, notify customer.	
			cout << "buffer is full." << endl;
			pthread_cond_wait(&cond, &mutex);	
		}
		G_COUNT++;
		//notify customer.
		pthread_cond_signal(&cond);
		cout << "count " << G_COUNT << " producter " << (long)(pArg) << endl;
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_exit(0);
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t pidarr[3] = {0};

	//create customer.
	int ret = pthread_create(pidarr, NULL, Customer, (void *)1);
	if (0 != ret) {
		cout << "Create customer error." << endl;
		return -1;
	}

	//create producter.
	ret = pthread_create(pidarr + 1, NULL, Producter, (void *)2);
	if (0 != ret) {
		cout << "Create producter error." << endl;
		return -1;
	}

	ret = pthread_create(pidarr + 2, NULL, Producter, (void *)3);
	if (0 != ret) {
		cout << "Create producter error." << endl;
		return -1;
	}

	pthread_join(pidarr[0], NULL);
	pthread_join(pidarr[1], NULL);
	pthread_join(pidarr[2], NULL);
	return 0;
}
