
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <memory.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//truct msqid_ds {
//	struct ipc_perm msg_perm;     /* Ownership and permissions */
//	time_t          msg_stime;    /* Time of last msgsnd(2) */
//	time_t          msg_rtime;    /* Time of last msgrcv(2) */
//	time_t          msg_ctime;    /* Time of last change */
//	unsigned long   __msg_cbytes; /* Current number of bytes in
//									 queue (nonstandard) */
//	msgqnum_t       msg_qnum;     /* Current number of messages
//									 in queue */
//	msglen_t        msg_qbytes;   /* Maximum number of bytes
//									 allowed in queue */
//	pid_t           msg_lspid;    /* PID of last msgsnd(2) */
//	pid_t           msg_lrpid;    /* PID of last msgrcv(2) */
//};
//
//struct ipc_perm {
//	key_t          __key;       /* Key supplied to msgget(2) */
//	uid_t          uid;         /* Effective UID of owner */
//	gid_t          gid;         /* Effective GID of owner */
//	uid_t          cuid;        /* Effective UID of creator */
//	gid_t          cgid;        /* Effective GID of creator */
//	unsigned short mode;        /* Permissions */
//	unsigned short __seq;       /* Sequence number */
//};

//get msgqueue info
int main01(void)
{
	int msgid = msgget(0x1235, 0666 | IPC_CREAT);
	if (msgid < 0) {
		perror("msgid error:");
	}
	struct msqid_ds stat;
	memset(&stat, 0, sizeof(struct msqid_ds));
	if (-1 == msgctl(msgid, IPC_STAT, &stat)) {
		perror("msgctl error:");
	}
	printf("perm is %o.\n", stat.msg_perm.mode);
	printf("bytes in queue %ld.\n", stat.__msg_cbytes);
	printf("number of msg is queue %u.\n", stat.msg_qnum);
	return 0;
}

//set msqid_ds, first get msqid_ds, then set value by define struct msqid_ds
int main02(void)
{
	int msgid = msgget(0x1235, 0666 | IPC_CREAT);
	if (msgid < 0) {
		perror("msgid error:");
	}
	struct msqid_ds stat;
	memset(&stat, 0, sizeof(struct msqid_ds));
	if (-1 == msgctl(msgid, IPC_STAT, &stat)) {
		perror("msgctl error:");
	}
//	printf("perm is %o.\n", stat.msg_perm.mode);
//	printf("bytes in queue %ld.\n", stat.__msg_cbytes);
//	printf("number of msg is queue %u.\n", stat.msg_qnum);

	stat.msg_perm.mode = 0444;
	if (msgctl(msgid, IPC_SET, &stat) < 0) {
		perror("msgctl error:");
	}
	return 0;
}

int main(void)
{
	int msgid = msgget(0x1235, 0444 | IPC_CREAT);
	if (msgid < 0) {
		perror("msgid error:");
	}
	struct msqid_ds stat;
	memset(&stat, 0, sizeof(struct msqid_ds));
	if (-1 == msgctl(msgid, IPC_RMID, NULL)) {
		perror("msgctl error:");
	}
	return 0;
}
