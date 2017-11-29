/****************************************************************************
**
**  Copyright (C) 2017 liushixiongcpp@163.com
**  All rights reserved.
**
****************************************************************************/

#ifndef _pub_h
#define _pub_h

#include <list>
#include <algorithm>

using std::list;

//C2S
#define C2S_LOGIN           0x01
#define C2S_LOGOUT          0x02
#define C2S_ONLINE_USER     0x03

#define MSG_LEN             512 

//S2C
#define S2C_LOGIN_OK        0x04
#define S2C_ALREADY_LOGINED 0x05
#define S2C_SOMEONE_ONLINE  0x06
#define S2C_SOMEONE_LOGOUT  0x07
#define S2C_ONLINE_USER     0x08

//C2C
#define C2C_CHAT            0x09

typedef struct message 
{
    int cmd;
    char body[MSG_LEN];
} MESSAGE;

typedef struct user_info
{
    char username[16];
    unsigned int ip;
    unsigned short port;
} USER_INFO;

typedef struct chat_msg
{
    char username[16];   
    char msg[100];
} CHAT_MSG;

typedef list<USER_INFO> USER_LIST;

#endif //_pub_h
