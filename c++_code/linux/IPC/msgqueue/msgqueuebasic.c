/*
 * about basic msgqueue API.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//error:No such file and directory
int main01(void)
{
	int msgid = msgget(0x1234, 0666);
	if (msgid < 0) {
		perror("getmsg error:");
	}
	else {
		printf("msgid is %d.\n", msgid);
	}
	return 0;
}


//if 0x1234 already existed, then get id.
//else create 0x1234 message queue.
int main02(void)
{
	int msgid = msgget(0x1234, 0666 | IPC_CREAT);
	if (msgid < 0) {
		perror("getmsg error:");
	}
	else {
		printf("msgid is %d.\n", msgid);
	}
	return 0;
}


//IPC_EXCL has to use with IPC_CREAT
//repsent to if msgid also existed then occur err and set errno
//else create new message queue
int main03(void)
{
	int msgid = msgget(0x1235, 0666 | IPC_CREAT | IPC_EXCL);
	if (msgid < 0) {
		if (errno == EEXIST) {
			printf("msg id also existed.\n");
		}
		perror("getmsg error:");
	}
	else {
		printf("msgid is %d.\n", msgid);
	}
	return 0;
}

//create private message queue
//if msgget id set IPC_PRIVATE everytime create msgqueue is diffirent
//also IPC_CREAT and IPC_EXCL will not useful
//also this msgqueue only parent and this family can operation.
int main(void)
{
	int msgid = msgget(0x1235, 0666 | IPC_CREAT | IPC_EXCL);
	if (msgid < 0) {
		if (errno == EEXIST) {
			printf("msg id also existed.\n");
		}
		perror("getmsg error:");
	}
	else {
		printf("msgid is %d.\n", msgid);
	}
	return 0;
}

