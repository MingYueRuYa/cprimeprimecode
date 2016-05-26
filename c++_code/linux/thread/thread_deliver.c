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
//thread and process deliver info

typedef struct _Teacher {
	char name[64];
	int  age;
}Teacher;

void *thread_routine(void *arg)
{
	pthread_detach(pthread_self());
	Teacher *t1 = (Teacher *)arg;
	printf("name:%s, age:%d.\n", t1->name, t1->age++);
	t1->age += 2;
	//pthread_exit(arg);
	//use return to return value and pthread_exit(arg) is same.
	return arg;
}

//this is error usage.
//attention:not return local variable.
void *thread_routine_err(void *arg)
{
	pthread_detach(pthread_self());
	Teacher t1 = {"unix", 20};
	return &t1;
}

int main(int argc, char *argv[])
{
	printf("main start...\n");
	Teacher teacher = {"linux", 10};
	pthread_t tid;
	pthread_create(&tid, NULL, thread_routine, &teacher);
	Teacher *tpoint = &teacher;
	printf("thread return val.\n");
	pthread_join(tid, &tpoint);
	printf("name:%s, age:%d.\n", tpoint->name, tpoint->age++);

	//error usage.
	pthread_t errid;
	pthread_create(&errid, NULL, thread_routine_err, &teacher);
	tpoint = NULL;
	printf("thread return val.\n");
	pthread_join(errid, &tpoint);
	printf("name:%s, age:%d.\n", tpoint->name, tpoint->age++);

	return 0;
}
