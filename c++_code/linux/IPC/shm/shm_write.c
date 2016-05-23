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
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct _Teacher {
	char name[64];
	int age;
}Teacher;

int main(int argc, char *argv[])
{
	int shmid = shmget(0x1234, sizeof(Teacher), IPC_CREAT | 0666);
	if (shmid < 0) {
		perror("shmget error");
		exit(-1);
	}
	Teacher *teacher = shmat(shmid, NULL, 0);
	if (teacher < 0) {
		perror("shmat error");
		exit(-1);
	}
	teacher->age = 10;	
	strcpy(teacher->name, "linux");
	while (1) {

	}
	return 0;
}
