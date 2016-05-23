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

#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct _Teacher {
	char name[64];
	int age;
}Teacher;

int main(int argc, char *argv[])
{
	int shmid = 0;
	if((shmid = shmget(0x1234, sizeof(Teacher), IPC_CREAT | 0666)) < 0) {
		perror("shmget error");	
		exit(-1);
	}
	Teacher *teacher = shmat(shmid, NULL, 0);	
	if (teacher < 0) {
		perror("shmat error");
		exit(-1);
	}
	printf("teacher name %s, age %d.\n", teacher->name, teacher->age);
	printf("enter 1 is delete shm, 0 is pause, 2 is deattach, other is exit.\n");
	int flag;
	scanf("%d", &flag);
	if (1 == flag) {
		//deattach shm
		shmdt(teacher);
		//delete shm
		shmctl(shmid, IPC_RMID, NULL);
	}
	else if (0 == flag) {
		pause();
	}
	else if (2 == flag) {
		shmdt(teacher);
		pause();
	}
	else {
		exit(0);
	}
	while (1) {

	}
	return 0;
}
