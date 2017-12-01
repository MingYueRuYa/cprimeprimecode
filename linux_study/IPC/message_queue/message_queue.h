/****************************************************************************
**
**  Copyright (C) 2017 liushixiongcpp@163.com
**  All rights reserved.
**
****************************************************************************/

#ifndef _message_queue_h
#define _message_queue_h

#include <stdbool.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define APPLICATION_NAME "msgqueue"

#define ERR_EXIT(message)   \
    do { \
        perror(message);   \
        exit(EXIT_FAILURE); \
    } while(0)

#define MSGMAX 8192

typedef struct ARGSINFO {
    key_t msgkey;
	int msgid;
    int creat;
    int open;
    int flag;
    int type;
    int opt;
    int mode;
	int recvtype;

    bool isopen;
    bool iscreat;
    bool issend;
	bool isrecv;
} Args_Info;

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

void print_message_info();

void print_help();

#endif /* _message_queue_h */
