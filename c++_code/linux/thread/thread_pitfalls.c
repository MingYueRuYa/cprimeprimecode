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
 *  multi thread pitfalls.
 *  send msg to peer thread.
 * */

typedef struct Teacher {
	char name[64];
	int age;
}Teacher;

void *thread_routine(void *arg)
{
	printf("this is thread.\n");
	//if thread attribute set detach, then thread end os will be recyle resource. but not use pthread_join recyle
	//detach status thread resource.
	//int ret = pthread_detach(pthread_self());
	int i = 0;
	Teacher *pteacher = (Teacher *)arg;
	printf("tid %u, teacher age is %d.\n",pthread_self(), pteacher->age);
//	int loop = (int)arg;
//	for (; i < loop; ++i) {
//		printf("thread is %u, loop %d.\n", pthread_self(), i);
//	}
//	sleep(3);
	pthread_exit(arg);
}

int main(int argc, char *argv[])
{
	int i = 0;
	int num = 10;
	int loop = 20;
	pthread_t tidarray[200];
	pthread_t tid;
	printf("please enter thread number:\n");
	scanf("%d", &num);
	printf("please enter thread loops:\n");
	scanf("%d", &loop);

	Teacher teacher[200] = {0};
	for (; i < num; ++i) {
		/*
		 * attention: there is pitfalls, every time send teacher struct is diffirent. so ensure every thread has 
		 * diffirent teacher cache address. if not send diffirent teacher cache address, peer thread will have
		 * some teacher address, this will be pitfalls.
		 * */
		//first way to solve pitfalls.
		memset(&teacher[i], 0, sizeof(Teacher));
		teacher[i].age = i;

		//second way to solve pitfalls.
		//dynamic memory
		//teacher = (Teacher *)(malloc(Teacher));
		pthread_create(&tidarray[i], NULL, thread_routine, &teacher[i]);
	}

	void *retval = NULL;
	for (i = 0; i < num; ++i) {
		//printf("index %d, tid %u.\n", i, tidarray[i]);
		//int ret = pthread_join(tidarray[i], &retval);
		int ret = pthread_join(tidarray[i], &retval);
		//printf("ret %d.\n", ret);
	}
	printf("main exit.\n");
	return 0;
}
