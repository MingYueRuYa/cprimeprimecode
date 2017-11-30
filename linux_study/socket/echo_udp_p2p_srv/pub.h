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
#define S2C_BASE            0x200
#define S2C_LOGIN_OK        S2C_BASE+1
#define S2C_ALREADY_LOGINED S2C_BASE+2
#define S2C_SOMEONE_ONLINE  S2C_BASE+3
#define S2C_SOMEONE_LOGOUT  S2C_BASE+4
#define S2C_ONLINE_USER     S2C_BASE+5
#define S2C_SERVER_LOGOUT   S2C_BASE+6

//C2C
#define C2C_BASE            0x400
#define C2C_CHAT            C2C_BASE+1

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
