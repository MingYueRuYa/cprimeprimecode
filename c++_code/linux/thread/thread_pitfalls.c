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
 * */

typedef struct Teacher {
	char name[64];
	int age;
}Teacher;

void *thread_routine(void *arg)
{
	printf("this is thread.\n");
	int ret = pthread_detach(pthread_self());
	int i = 0;
	Teacher *pteacher = (Teacher *)arg;
	printf("teacher age is %d.\n", pteacher->age);
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

	Teacher teacher;
	for (; i < num; ++i) {
		memset(&teacher, 0, sizeof(teacher));
		teacher.age = i;
		pthread_create(&tidarray[i], NULL, thread_routine, &teacher);
	}

	for (i = 0; i < num; ++i) {
		int ret = pthread_join(tidarray[i], NULL);
		printf("ret %d.\n", ret);
	}
	printf("main exit.\n");
	return 0;
}