/*
 * about basic msgqueue API.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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
int main04(void)
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

//test permissions
//attention: there is permission denied.
int main05(void)
{
	int msgid = msgget(0x1235, 0666 | IPC_CREAT);
	if (msgid < 0) {
		if (errno == EEXIST) {
			printf("msg id also existed.\n");
		}
		perror("getmsg error:");
	}
	else {
		printf("msgid is %d.\n", msgid);
	}
	int _msgid = msgget(0x1235, 0144);
	printf("_msgid is %d.\n", _msgid);
	if (_msgid < 0) {
		perror("msgget error:");
	}
	return 0;
}

struct msgbuf {
	long mtype;
	char mtext[1024];
};

int main(void)
{
	int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
	struct msgbuf buf;
	memset(&buf, 0, sizeof(struct msgbuf));
	buf.mtype = 1;
	strcpy(buf.mtext, "YunOs");
	if (msgsnd(msgid, &buf, strlen(buf.mtext), 0) < 0) {
		perror("msgsnd error");
		return -1;
	}
	return 0;
}
