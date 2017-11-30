#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "pub.h"

#define ERR_EXIT(msg)   \
    do {    \
        perror(msg);    \
        exit(EXIT_FAILURE);  \
    } while(0)

#define PORT    5188
#define IP      "127.0.0.1"

char username[16]   = {0};

struct sockaddr_in addr;

int serverfd = 0;

USER_LIST client_list;

void do_someone_login(MESSAGE &msg);
void do_someone_logout(MESSAGE &msg);
void do_getlist(int sock, struct sockaddr_in *servaddr);
void do_chat(MESSAGE &msg);
void do_exit(int sock, struct sockaddr_in *servaddr);

void parse_cmd(char *cmdline, int sock, struct sockaddr_in *servaddr);
bool sendmsgto(int sock, char *username, char *msg);

void TipMessage();

void do_client(/*int sockfd*/)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        ERR_EXIT("socket");        
    }
    serverfd = sockfd;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);
    socklen_t len        = sizeof(struct sockaddr_in);
    // 这里不能再绑定connect到服务器
    // 因为一旦绑定了，则sockfd就不能与其他的client通信
    // int ret = connect(sockfd, (struct sockaddr *)&addr, len);
    // if (ret < 0) {
        // ERR_EXIT("socket");        
    // }

    MESSAGE msg;

    socklen_t socklen = sizeof(sockaddr);

    while (1) {
        memset(username, 0, sizeof(username));
        
        printf("Please input your name:");
        fflush(stdout);
        scanf("%s", username);

        memset(&msg, 0, sizeof(MESSAGE));
        msg.cmd = htonl(C2S_LOGIN);
        strcpy(msg.body, username);
        sendto(sockfd, &msg, sizeof(MESSAGE), 0
                , (struct sockaddr *)&addr, socklen);

        memset(&msg, 0, sizeof(MESSAGE));
        recvfrom(sockfd, &msg, sizeof(msg), 0
                , (struct sockaddr *)&addr, &socklen);
        int cmd = ntohl(msg.cmd);
        if (cmd == S2C_ALREADY_LOGINED) {
            printf("user %s already logined server"
                    ", please user another username\n"
                    , username);
        } else if (cmd == S2C_LOGIN_OK) {
            printf("user %s has logined server\n", username);
            break;
        }
    }

    int count;
    recvfrom(sockfd, &count, sizeof(int), 0
            , (struct sockaddr *)&addr, &socklen);
    int n = ntohl(count);
    printf("has %d user loinged server\n", n);

    for (int i=0; i<n; ++i) {
        USER_INFO user;
        recvfrom(sockfd, &user, sizeof(USER_INFO), 0
                , (struct sockaddr *)&addr, &socklen);
        client_list.push_back(user);
        in_addr tmp;
        tmp.s_addr = user.ip;
        printf("%d %s <-> %s:%d\n", i, user.username
                , inet_ntoa(tmp)
                , ntohs(user.port));
    }

    TipMessage();

    fd_set rset;
    FD_ZERO(&rset);
    int nready;
    while (1) {
        FD_SET(STDIN_FILENO, &rset);
        FD_SET(sockfd, &rset);
        nready = select(sockfd+1, &rset, NULL, NULL, NULL);
        if (-1 == nready) {
            if (errno == EINTR) {
                continue;
            } else {
                ERR_EXIT("select");
            } // if
        } 

        if (0 == nready) {   //超时中断
            continue;
        } 

        if (FD_ISSET(sockfd, &rset)) {
            memset(&msg, 0, sizeof(MESSAGE));
            struct sockaddr_in peer;
            len = sizeof(peer);
            recvfrom(sockfd, &msg, sizeof(MESSAGE), 0
                    , (struct sockaddr *)&peer, &len);
            int cmd = ntohl(msg.cmd);
            switch(cmd) {
                case S2C_SOMEONE_ONLINE:
                    do_someone_login(msg);
                    break;
                case S2C_SOMEONE_LOGOUT:
                    do_someone_logout(msg);
                    break;
                case S2C_ONLINE_USER:
                    do_getlist(sockfd, &addr);
                    break;
                case C2C_CHAT:
                    do_chat(msg);
                    break;
                default:
                    printf("unkown command, cmd:%d!\n", cmd);
                    break;
            } // switch
            TipMessage();
        } // if FD_ISSET

        if (FD_ISSET(STDIN_FILENO, &rset)) {
            char cmdline[100] = {0};
            if (fgets(cmdline, sizeof(cmdline), stdin) == NULL) {
                break;
            }

            // printf("cmd line %s\n", cmdline);
            
            if (cmdline[0] == '\n') {
                continue;
            }

            cmdline[strlen(cmdline)-1] = '\0';
            parse_cmd(cmdline, sockfd, &addr);
        }

    } // while

    close(sockfd);
}

void do_someone_login(MESSAGE &msg)
{
   USER_INFO *user = (USER_INFO *)msg.body;
   in_addr tmp;
   tmp.s_addr = user->ip;
   printf("%s <-> %s:%d has logined server\n"
           , user->username
           , inet_ntoa(tmp)
           , ntohs(user->port));
   client_list.push_back(*user);
}

void do_someone_logout(MESSAGE &msg)
{
    USER_LIST::iterator it;
    for (it = client_list.begin(); it != client_list.end(); ++it) {
        if (0 == strcmp(msg.body, it->username)) {
            break; 
        }
    }

    if (it != client_list.end()) {
        client_list.erase(it);
    }

    printf("user %s has not logined server\n", msg.body); 
}

void do_getlist(int sock, struct sockaddr_in *servaddr)
{
    
    socklen_t socklen = sizeof(*servaddr);
    int count = 0;
    recvfrom(sock, &count, sizeof(int), 0
            , (struct sockaddr *)servaddr, &socklen);
    printf("has %d users logined server\n", ntohl(count));
    client_list.clear();

    int n = ntohl(count);
    for (int i=0; i<n; ++i) {
        USER_INFO user;
        recvfrom(sock, &user, sizeof(USER_INFO), 0
                , (struct sockaddr *)servaddr, &socklen);
        client_list.push_back(user);

        in_addr tmp;
        tmp.s_addr = user.ip;

        printf("%s <-> %s:%d\n", user.username
                , inet_ntoa(tmp)
                , ntohs(user.port));
    }
}

void do_chat(MESSAGE &msg)
{
    CHAT_MSG *cm = (CHAT_MSG *)msg.body;
    printf("recive a msg [%s] from [%s]\n", cm->msg, cm->username);
}

void do_exit(int sock, struct sockaddr_in *servaddr)
{
    MESSAGE msg;
    memset(&msg, 0, sizeof(MESSAGE));
    msg.cmd = htonl(C2S_LOGOUT);
    strcpy(msg.body, username);
    socklen_t socklen = sizeof(sockaddr);
    if (sendto(sock, &msg, sizeof(MESSAGE), 0
            , (struct sockaddr *)servaddr, socklen) < 0) {
        ERR_EXIT("sendto");
    }
    printf("client exit\n");
    exit(EXIT_SUCCESS);
}

void parse_cmd(char *cmdline, int sock, struct sockaddr_in *servaddr)
{
    char cmd[10] = {0};
    char *p; 
    p = strchr(cmdline, ' ');
    if (p != NULL) {
        *p = '\0';
    }
    // 注意这里需要去掉cmdline的前后空格
    // TODO 去掉前后的空格
    strcpy(cmd, cmdline);

    socklen_t socklen = sizeof(*servaddr);

    if (0 == strcmp(cmd, "exit")) {
        do_exit(sock, servaddr);
    } else if (0 == strcmp(cmd, "send")) {
        char peername[16] = {0};
        char msg[MSG_LEN] = {0};
        // send user msg
        //      p    p2
        while (*p++ == ' ') ;
        char *p2;
        p2 = strchr(p, ' ');
        if (p2 == NULL) {
            TipMessage();
            return;
        }
        *p2 = '\0';
        strcpy(peername, p);
        while (*p2++ == ' ') ;
        strcpy(msg, p2);
        sendmsgto(sock, peername, msg);
    } else if (0 == strcmp(cmd, "list")) {
        MESSAGE msg;
        memset(&msg, 0, sizeof(MESSAGE));
        msg.cmd = htonl(C2S_ONLINE_USER);
        strcpy(msg.body, username);
        if (sendto(sock, &msg, sizeof(msg), 0
                , (struct sockaddr *)servaddr, socklen) < 0) {
            ERR_EXIT("sendto");
        }
    } else {
        TipMessage();
    }
}

bool sendmsgto(int sock, char *name, char *msg)
{
    if (0 == strcmp(username, name)) {
        printf("can't send message to self\n");
        return false;
    }

    USER_LIST::iterator it;
    for (it = client_list.begin(); it != client_list.end(); ++it) {
        if (0 == strcmp(name, it->username)) {
            break; 
        }
    }

    if (it == client_list.end()) {
        printf("user %s has not logined server\n", name);
        return false;
    }

    MESSAGE sendmsg;
    memset(&sendmsg, 0, sizeof(MESSAGE));
    sendmsg.cmd = htonl(C2C_CHAT);

    CHAT_MSG cm;
    strcpy(cm.username, username);
    strcpy(cm.msg, msg);

    memcpy(sendmsg.body, &cm, sizeof(CHAT_MSG));

    struct sockaddr_in peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_port   = it->port;
    peeraddr.sin_addr.s_addr = it->ip;

    in_addr tmp;
    tmp.s_addr   = it->ip;

    printf("sending message [%s] to user [%s] <-> %s:%d\n "
            , msg, name, inet_ntoa(tmp), ntohs(it->port));

    socklen_t socklen = sizeof(sockaddr);
    if (sendto(sock, &sendmsg, sizeof(sendmsg), 0
                    , (struct sockaddr *)&peeraddr
                    , socklen) < 0) {
        perror("sendto");
    }

    return true;
}

void handle_sigint(int signum)
{
    do_exit(serverfd, &addr);
}

void TipMessage()
{
    printf("\nCommand are:\n");
    printf("send name msg:\n");
    printf("list\n");
    printf("exit\n");
    printf("\n");
}

int main(int argc, char *argv[])
{

    signal(SIGINT, handle_sigint);

    do_client();

    return 0;
}
