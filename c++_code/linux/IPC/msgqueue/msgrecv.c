#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct msgbuf {
	long mtype;
	char mtext[1024];
};

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("Usage: %s <msgtype> <length>.\n",argv[0]);
		return 0;
	}
	int type = atoi(argv[1]);
	printf("type %d.\n", type);
	int len = atoi(argv[2]);
	int msgid = msgget(0x1235, 0666);
	if (msgid < 0) {
		perror("msgget error:");
		return -1;
	}
	struct msgbuf buf;
	memset(&buf, 0, sizeof(struct msgbuf));
	printf("start....id %d.\n", msgid);
	ssize_t rcvlen = msgrcv(msgid, &buf, 1024, type, IPC_NOWAIT);
	if (rcvlen < 0) {
		perror("msgrcv error:");
		return -1;
	}
	buf.mtext[rcvlen] = '\0';
	printf("recv message %s, type %d.\n", buf.mtext, buf.mtype);
	return 0;
}


