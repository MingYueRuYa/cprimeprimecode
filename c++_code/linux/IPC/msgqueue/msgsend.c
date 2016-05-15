#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

//long maybe 8 betys or 4 bytes, it all denpends pc structe
int test_long_and_int_size(void)
{
	printf("sizeof(long):%lu.\n", sizeof(long));
	printf("sizeof(int):%lu.\n", sizeof(int));
	return 0;
}

struct msgbuf {
	long mtype; //message type, must be > 0
	char mtext[1024]; // message data
};

int main(int argc, char *argv[])
{
	int msgid = 0;	
	int ret = 0;
	if (3 != argc) {
		fprintf(stderr, "Usage: %s <message type> <message length bytes> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int type = atoi(argv[1]);
	int len = atoi(argv[2]);

	msgid = msgget(0x1235, 0666 | IPC_CREAT);
	if (msgid < 0) {
		if (errno == ENOENT) {
			printf("message queue is not exist.\n");	
		}
		else if (errno == EEXIST) {
			printf("message queue is exist.\n");	
		}
		perror("msggget error:");
		return -1;
	}
	printf("msgid is %d.\n", msgid);

	struct msgbuf buf;
	memset(&buf, 0, sizeof(struct msgbuf));
	buf.mtype = type;
	printf("buf.mtype %d.\n", type);
	strcpy(buf.mtext, "I like linux os.");
	
	//test max avaliable bytes.
	//int i = 0;
	//for (; i < 8 * 1024 + 1; ++i) {
		ret = msgsnd(msgid, &buf, len, IPC_NOWAIT);
		if (ret < 0) {
			perror("msgsnd error:");
			return -1;
		}
	//}

	return 0;
}
