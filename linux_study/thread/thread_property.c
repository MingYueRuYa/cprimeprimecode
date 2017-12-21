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

int main(int argc, char *argv[])
{
	pthread_attr_t attr;	
	pthread_attr_init(&attr);

	int state = 0;
	pthread_attr_getdetachstate(&attr, &state);
	if (state == PTHREAD_CREATE_JOINABLE) {
		printf("detachstate:PTHREAD_CREATE_JOINABLE\n");
	} else if (state == PTHREAD_CREATE_DETACHED) {
		printf("detachstate:PTHREAD_CREATE_DETACHED\n");
	}

	size_t size = 0;
	pthread_attr_getstacksize(&attr, &size);
	printf("stacksize:%d\n", size);

	int scope = 0;
	pthread_attr_getscope(&attr, &scope);
	if (scope == PTHREAD_SCOPE_PROCESS) {
		printf("scope:PTHREAD_SCOPE_PROCESS\n");
	} else if (scope == PTHREAD_SCOPE_SYSTEM) {
		printf("scope:PTHREAD_SCOPE_SYSTEM\n");
	}

	int policy = 0;
	pthread_attr_getschedpolicy(&attr, &policy);
	if (policy == SCHED_FIFO) {
		printf("scope:SCHED_FIFO\n");
	} else if (policy == SCHED_RR) {
		printf("scope:SCHED_RR\n");
	} else if (policy == SCHED_OTHER) {
		printf("scope:SCHED_OTHER\n");
	}

	int inheritsched = 0;
	pthread_attr_getinheritsched(&attr, &policy);
	if (inheritsched == PTHREAD_INHERIT_SCHED) {
		printf("inheritsched:PTHREAD_INHERIT_SCHED\n");
	} else if (inheritsched == PTHREAD_EXPLICIT_SCHED) {
		printf("inheritsched:PTHREAD_EXPLICIT_SCHED\n");
	}
	struct sched_param param;
	pthread_attr_getschedparam(&attr, &param);
	printf("sched_priority:%d\n", param.sched_priority);

	pthread_attr_destroy(&attr);

	int level = pthread_getconcurrency();
	printf("level:%d\n", level);

// result:
	// detachstate:PTHREAD_CREATE_JOINABLE
	// stacksize:8388608
	// scope:PTHREAD_SCOPE_SYSTEM
	// scope:SCHED_OTHER
	// inheritsched:PTHREAD_INHERIT_SCHED
	// sched_priority:0
	// level:0

	return 0;
}
