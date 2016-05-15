/*
 * test all api
 * */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
	long mtype;
	char mtext[1024];
};

int main(int argc, char *argv[])
{
	key_t key;
	int msgid = 0;
	int ret = 0;
	int msgtype = getpid();

	//attention: kefile must existed before.
	key = ftok("./keyfile", 'a');
	printf("key = [%x].\n", key);
	msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
	if (msgid < 0) {
		if (errno == EEXIST) {
			printf("EXIST...\n");
			key = ftok("./keyfile", 'a');
			msgid = msgget(key, 0666 | IPC_CREAT);
		}
		else {
			perror("msgget error:");
			return -1;
		}
	}
	printf("msgid is %d.\n", msgid);
	
	struct msgbuf buf;
	memset(&buf, 0, sizeof(struct msgbuf));
	buf.mtype = msgtype;
	strcpy(buf.mtext, "I like linux os.");
	if (msgsnd(msgid, &buf, strlen(buf.mtext), IPC_NOWAIT) < 0) {
		perror("msgsnd error:");
		return -1;
	}
	sleep(1);

	memset(&buf, 0, sizeof(struct msgbuf));
	//attention:len parameter must be greater than or equal send msgsnd function msg len.
	ssize_t retsize = msgrcv(msgid, &buf, sizeof(buf.mtext), 0, IPC_NOWAIT);
	if (retsize < 0) {
		perror("msgrcv error:");
		return -1;
	}
	buf.mtext[retsize] = '\0';
	printf("msg %s.\n", buf.mtext);
	return 0;
}
