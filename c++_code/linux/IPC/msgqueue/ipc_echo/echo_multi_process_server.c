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

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_LEN 1024

struct msgbuf {
	long mtype;
	char mtext[BUF_LEN];
};

int echo_server()
{
	int typeid[1024] = {0};
	key_t key = ftok("/tmp/", 'a');
	if (key < 0) {
		perror("fotk error");
		return -1;
	}
	int msgid = msgget(key, 0666 | IPC_CREAT);	
	if (msgid < 0) {
		perror("msgget error");
		return -1;
	}
	
	struct msgbuf buf;	
	memset(&buf, 0, sizeof(struct msgbuf));
	int retlen = 0;
	int mtype = 0;
	while ((retlen = msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0)) > 0) {
		printf("recv %s", buf.mtext + 4);
		mtype = *((int *)buf.mtext);
		buf.mtype = mtype;
		//strlen(buf.mtext + 4) + 4 calc length, because mtype is int type maybe have 0 byte.
		if (msgsnd(msgid, &buf, strlen(buf.mtext + 4) + 4, 0) < 0) {
			perror("msgsnd error");
			continue;
		}
		memset(&buf, 0, sizeof(struct msgbuf));
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int ret = echo_server();
	return ret;
}
