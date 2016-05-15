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

/*
 * thinking:
 * client send msg to server(actually send to linux kernel) then mstype is 1.
 * server return msg(actually return to linux kernel) then mstype is client pid.
 * so, linux kernel control message queue
 * model:
 *				client -->	linux kernel --> server
 *				client <--	linux kernel <-- server
 * */

#define BUF_LEN 1024
#define TYPE 1

struct msgbuf {
	long mtype;
	char mtext[BUF_LEN];
};

int echo_client()
{
	//get key value by ftok, every app get key by this way, to ensure key is same. also, this is common way used in company.
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
	pid_t mtypepid = getpid();
	*((int *)buf.mtext) = mtypepid;
	while (fgets(buf.mtext + 4, BUF_LEN, stdin) != NULL) {
		buf.mtype = TYPE;
		if (msgsnd(msgid, &buf, strlen(buf.mtext + 4) + 4, IPC_NOWAIT) < 0) {
			perror("msgsnd error");
			return -1;
		}
		memset(buf.mtext + 4, 0, BUF_LEN - 4);
		int retlen = 0;
		if ((retlen = msgrcv(msgid, &buf, sizeof(struct msgbuf), mtypepid, 0)) < 0) {
			perror("msgrcv error");
			continue;
		}
		printf("retlen %d.\n", retlen);
		printf("receive from server: %s", buf.mtext + 4);
		memset(buf.mtext + 4, 0, BUF_LEN - 4);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int ret = echo_client();
	return ret;
}

