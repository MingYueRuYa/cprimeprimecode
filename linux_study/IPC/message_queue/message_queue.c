/****************************************************************************
**
**  Copyright (C) 2017 liushixiongcpp@163.com
**  All rights reserved.
**
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define APPLICATION_NAME "msgqueue"

#define ERR_EXIT(message)   \
    do { \
        perror(message);   \
        exit(EXIT_FAILURE); \
    } while(0)

typedef struct msg_queue_info {
    int mode;
    unsigned long current_bytes; 
    unsigned long current_number; 
    unsigned long max_bytes;
} msg_queue_info; 

typedef struct msgbuf {
    long mtype;
    char mtext[1];
} msgbuf;

typedef struct ARGSINFO {
    key_t msgkey;
    int creat;
    int open;
    int flag;
    int type;
    int opt;
    int mode;

    bool isopen;
    bool iscreat;
    bool issend;
} Args_Info;

Args_Info  args_info;

/*
 *  创建消息队列
 * */
int create_message(key_t messageid, int msgflag);

/*
 * 打开消息队列
 * */
int open_message(key_t messageid, int msgflag);

/*
 * 获取消息队列属性
 * */
int get_message_queue_info(key_t msgid, msg_queue_info *info);

/*
 * 设置消息队列内容
 * */
int set_message_queue_info(key_t msgid, msg_queue_info *info);

/*
 * 发送消息
 * */
int send_message(key_t msgid, long msgtype, const char *msginfo);

/*
 * 接收消息
 * */
int recv_message(key_t msgid, long msgtype, size_t length, char *msginfo);

void print(msg_queue_info *msgqueue);

void print_help();

int test_creat_set_msgqueue()
{
    int retid = create_message(1234, 0666 | IPC_CREAT);
    if (retid < 0) {
        ERR_EXIT("getmessage");
    }

    retid = create_message(1234, 0);  // 0表示以原有的权限打开
    if (retid < 0) {
        ERR_EXIT("getmessage");
    }

    printf("open message queue %d\n", retid);

    msg_queue_info info;
    memset(&info, 0, sizeof(info));
    if (get_message_queue_info(retid, &info) < 0) {
        ERR_EXIT("get_message_queue_info");
    }
    print(&info);

    info.mode = 0444;
    info.current_bytes  = 10;
    info.current_number = 10;
    info.max_bytes      = 2048;

    if (set_message_queue_info(retid, &info) < 0) {
        ERR_EXIT("set_message_queue_info");
    }
    print(&info);

//result:
    // open message queue 196608
    // -------------------get_message_queue_info-------------------
    // mode            = 666       
    // current bytes   = 0         
    // current nums    = 0         
    // current bytes   = 16384     
    // -------------------set_message_queue_info-------------------
    // current bytes   = 10        
    // current nums    = 10        
    // current bytes   = 2048      
    // 最后再用ipcs指令查看时发现只有mode改变，其他的都没有改变

    return 0;
}

int main(int argc, char *argv[])
{
    // test_creat_set_msgqueue();


    int opt = -1;
    while (1) {
        opt = getopt(argc, argv, "m:hc:o:nr:s:");
        if (opt == '?') {
            exit(EXIT_FAILURE);
        } else if (opt == -1) {
            break;
        }

        switch(opt) {
            case 'h':
                print_help();
                exit(EXIT_FAILURE);
                break;
            case 'm':
                args_info.msgkey = atoi(optarg);
                break;
            case 'c':
                args_info.iscreat = true;
                sscanf(optarg, "%o", &args_info.mode);
                break;
            case 'o':
                args_info.isopen = true;
                if (NULL != optarg) {
                    sscanf(optarg, "%o", &args_info.mode);
                }
                break;
            case 'n':
                args_info.flag |= IPC_NOWAIT;
                break;
            case 's':
                args_info.type    = atoi(optarg);
                args_info.issend  = true;
                break;
            default:
                break;
        } 
    } //while

    if (args_info.msgkey < 0) {
        printf("message key value not specify\n");
        exit(EXIT_FAILURE); 
    }

    int msgid = -1;
    if (args_info.iscreat) {
        msgid = create_message(args_info.msgkey
                , args_info.mode | args_info.flag);
        if (msgid < 0) {
            ERR_EXIT("create_message");
        }
    }

    if (args_info.isopen) {
        msgid = open_message(args_info.msgkey, args_info.mode);
        if (msgid < 0) {
            ERR_EXIT("open_message");
        }
    }

    if (msgid < 0) {
        printf("please create or open message queue\n");
        exit(EXIT_FAILURE);
    }

    int ret = 0;

    if (args_info.issend) {
        ret = send_message(msgid, args_info.type, "linux");
        if (ret < 0) {
            ERR_EXIT("send_message");
        }
    }

    return;

    struct msg_queue_info info;
    memset(&info, 0, sizeof(info));
    ret = get_message_queue_info(msgid, &info);
    if (ret < 0) {
        ERR_EXIT("get_message_queue_info");
    }

    printf("-------------------set_message_queue_info-------------------\n");
    print(&info);

    char msg[1024] = {0};
    ret = recv_message(msgid, 1234, 5, msg);
    if (ret < 0) {
        ERR_EXIT("recv_message");
    }

    ret = get_message_queue_info(msgid, &info);
    if (ret < 0) {
        ERR_EXIT("get_message_queue_info");
    }

    printf("-------------------set_message_queue_info-------------------\n");
    print(&info);

    return 0;
}

int create_message(key_t messageid, int msgflag)
{
    // 以低权限创建，再以高权限打开就会出错，permission denied
    return msgget(messageid, msgflag);
}

int open_message(key_t messageid, int msgflag)
{
    int openflag = msgflag < 0 ? 0 : msgflag;
    return msgget(messageid, openflag);
}

int get_message_queue_info(key_t msgid, msg_queue_info *info)
{
    if (NULL == info) {
        errno = EINVAL;
        return -1;
    }

    struct msqid_ds buf;
    if (msgctl(msgid, IPC_STAT, &buf) < 0 ) {
        return -1;
    }

    info->mode              = buf.msg_perm.mode;
    info->max_bytes         = buf.msg_qbytes;
    info->current_bytes     = buf.__msg_cbytes;
    info->current_number    = buf.msg_qnum;
    return 0;
}

int set_message_queue_info(key_t msgid, msg_queue_info *info)
{
    if (NULL == info) {
        errno = EINVAL;
        return -1;
    }

    struct msqid_ds buf;
    memset(&buf, 0, sizeof(buf));
    if (msgctl(msgid, IPC_STAT, &buf) < 0 ) {
        return -1;
    }

    buf.msg_qnum      = info->current_number;
    buf.msg_qbytes    = info->max_bytes;    
    buf.__msg_cbytes  = info->current_bytes;
    buf.msg_perm.mode = info->mode;

    if (msgctl(msgid, IPC_SET, &buf) < 0 ) {
        return -1;
    }

    return 0;
}

int send_message(key_t msgid, long msgtype, const char *msginfo)
{
    if (NULL == msginfo) {
        errno = EINVAL;
        return -1;
    }

    struct msgbuf *buf;
    buf = (struct msgbuf *)malloc(sizeof(long)+strlen(msginfo));
    buf->mtype = msgtype;

    if (msgsnd(msgid, buf, strlen(msginfo), 0) < 0) {
        return -1;
    }

    free(buf);
    buf = NULL;
    return 0;
}

int recv_message(key_t msgid, long msgtype, size_t length, char *msginfo)
{
    if (NULL == msginfo) {
        errno = EINVAL;
        return -1;
    }

    struct msgbuf *buf;
    buf = (struct msgbuf *)malloc(sizeof(long)+length);
    buf->mtype = msgtype;

    if (msgrcv(msgid, buf, length, msgtype, 0) < 0) {
        return -1;
    }

    free(buf);
    buf = NULL;

    return 0;
}

void print(msg_queue_info *info)
{
    printf("mode            = %-10o\n",  info->mode);
    printf("current bytes   = %-10lu\n", info->current_bytes);
    printf("current nums    = %-10lu\n", info->current_number);
    printf("current bytes   = %-10lu\n", info->max_bytes);
}

void print_help()
{
    printf("%s [mcotn]\n", APPLICATION_NAME);
    printf("    -m specify message key\n");
    printf("    -c create with mode\n");
    printf("    -o open with mode, "
            "if mode=-1 means open origin permission.\n");
    printf("    -r recvie message with type\n");
    printf("    -s send message with type\n");
    printf("    -n with no wait\n");
    printf("for example:\n");
    printf("%s -c 666 creat message queue with 666 mode\n", APPLICATION_NAME);
}
