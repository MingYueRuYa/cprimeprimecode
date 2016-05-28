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
 * thread attribute.
 * */

int main(int argc, char *argv[])
{
	pthread_attr_t attr;
	//init attr
	pthread_attr_init(&attr);
	
	int state;
	//get detach statu
	pthread_attr_getdetachstate(&attr, &state);
	if (state == PTHREAD_CREATE_JOINABLE) {
		printf("detach state PHTREAD_CREATE_JOINABLE.\n");
	} 
	else if (state == PTHREAD_CREATE_DETACHED) { 
		printf("detach state PTHREAD_CREATE_DETACHED.\n");
	}

	size_t size;
	pthread_attr_getstacksize(&attr,&size);
	printf("stack size %u.\n", size);

	//stack overflow behind size
	//栈溢出的之后的空间大小
	pthread_attr_getguardsize(&attr, &size);
	printf("guard size %d.\n", size);
	
	int scope;
	//thread dispatch policy
	pthread_attr_getscope(&attr, &scope);	
	if (scope == PTHREAD_SCOPE_PROCESS) {
		//process inner dispatch
		printf("scope PTHREAD_SCOPE_PROCESS.\n");
	}
	else if (scope == PTHREAD_SCOPE_SYSTEM) {
		//system inner dispatch
		printf("scope PTHREAD_SCOPE_SYSTEM.\n");
	}

	int policy;
	pthread_attr_getschedpolicy(&attr, &policy);
	//FIFO plicy
	if (policy == SCHED_FIFO) { 
		printf("schedule policy FIFO.\n");
	}
	//if priority same, later will be first dispatch.
	else if (policy == SCHED_RR) {
		printf("schedule RR\n");
	}
	//other policy
	else if (policy == SCHED_OTHER) {
		printf("other schedule policy.\n");
	}

	//get thread priority.
	struct sched_param param;
	pthread_attr_getschedparam(&attr, &param);
	printf("schedule priority %d.\n", param.sched_priority);

	//detroy attr
	pthread_attr_destroy(&attr);

	//get concurrency level
	int level;
	//defualt value is 0, is represent kernel depends on map.
	level = pthread_getconcurrency();
	printf("level %d.\n", level);
	return 0;
}
