#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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

USER_LIST client_list;

void do_login(MESSAGE &msg, int sock, struct sockaddr_in *cliaddr);
void do_logout(MESSAGE &msg, int sock, struct sockaddr_in *cliaddr);
void do_sendlist(int sock, MESSAGE &msg, struct sockaddr_in *cliaddr);

void do_srv(int sockfd)
{
    struct sockaddr_in peeraddr;
    socklen_t len;

    MESSAGE msg;

    // int stdinfd = fileno(STDIN_FILENO);

    while (1) {
        memset(&msg, 0, sizeof(msg));
        len = sizeof(peeraddr);
        int ret = recvfrom(sockfd, &msg, sizeof(MESSAGE), 0
                , (struct sockaddr *)&peeraddr, &len);
        if (ret < 0 ) {
            if (errno == EINTR) {
                continue;
            } else {
                ERR_EXIT("recvfrom");
            }
        } else if (ret > 0) {
            int cmd = ntohl(msg.cmd);
            printf("recived cmd:%d\n", cmd);
            switch (cmd) {
                case C2S_LOGIN:
                    do_login(msg, sockfd, &peeraddr);
                    break;
                case C2S_LOGOUT:
                    do_logout(msg, sockfd, &peeraddr);
                    break;
                case C2S_ONLINE_USER:
                    do_sendlist(sockfd, msg, &peeraddr);
                    break;
                default:
                    break;
            } // switch
        } // if
    } // while 
    close(sockfd);
}

void do_login(MESSAGE &msg, int sock, struct sockaddr_in *cliaddr)
{
    USER_INFO user;
    strcpy(user.username, msg.body);
    user.ip     = cliaddr->sin_addr.s_addr;
    user.port   = cliaddr->sin_port;
    
    // 查找用户是否存在
    USER_LIST::iterator it;
    for (it = client_list.begin(); it != client_list.end(); ++it) {
        if (0 == strcmp(it->username, msg.body)) {
            break;
        }
    } // for it

    if (it == client_list.end()) {  //用户不存在
        printf("has a user login: %s <-> %s:%d\n"
                , msg.body
                , inet_ntoa(cliaddr->sin_addr)
                , ntohs(cliaddr->sin_port));     
        client_list.push_back(user);

        // 登陆成功应答 
        MESSAGE reply_msg; 
        memset(&reply_msg, 0, sizeof(MESSAGE));
        reply_msg.cmd = htonl(S2C_LOGIN_OK);
        socklen_t socklen = sizeof(sockaddr);
        sendto(sock, &reply_msg, sizeof(MESSAGE), 0
                , (struct sockaddr *)cliaddr
                , socklen);

        int count = htonl((int)client_list.size());
        //发送在线人数
        sendto(sock, &count, sizeof(int), 0
                , (struct sockaddr *)cliaddr, socklen);

        printf("sending user list information to: %s <-> %s:%d\n"
                , msg.body
                , inet_ntoa(cliaddr->sin_addr)
                , ntohs(cliaddr->sin_port));     

        for (it=client_list.begin(); it != client_list.end(); ++it) {
            if (sendto(sock, &*it, sizeof(USER_INFO), 0
                    , (struct sockaddr *)cliaddr, socklen) < 0) {
                if (errno == EINTR) {
                    continue;
                } else {
                    perror("sendto");
                }
            }
        } // for it

        // 向其他用户通知新用户登陆
        for (it=client_list.begin(); it != client_list.end(); ++it) {
            if (0 == strcmp(it->username, msg.body)) {
                continue;
            }

            struct sockaddr_in peeraddr;
            memset(&peeraddr, 0, sizeof(struct sockaddr_in));

            peeraddr.sin_family = AF_INET;
            peeraddr.sin_port   = it->port;
            peeraddr.sin_addr.s_addr = it->ip;
            msg.cmd = htonl(S2C_SOMEONE_ONLINE);
            memcpy(msg.body, &user, sizeof(user)); 

            sendto(sock, &msg, sizeof(MESSAGE), 0
                    , (struct sockaddr *)&peeraddr
                    , socklen);
        }

    } else {    // 找到用户
        printf("user %s has already logined\n", msg.body); 
        MESSAGE reply_msg;
        memset(&reply_msg, 0, sizeof(MESSAGE));
        reply_msg.cmd = htonl(S2C_ALREADY_LOGINED);
        sendto(sock, &reply_msg, sizeof(MESSAGE), 0
                , (struct sockaddr *)cliaddr
                , sizeof(sockaddr));
    }
}

void do_logout(MESSAGE &msg, int sock, struct sockaddr_in *cliaddr)
{
    printf("has a user logout : %s <-> %s:%d\n"
            , msg.body
            , inet_ntoa(cliaddr->sin_addr)
            , ntohs(cliaddr->sin_port));

    USER_LIST::iterator it; 
    for (it=client_list.begin(); it != client_list.end(); ++it) {
        if (0 != strcmp(it->username, msg.body)) {
            continue;
        }
        break;
    }

    if (it != client_list.end()) {
        client_list.erase(it);
    }

    // 向其他用户通知有用户退出
    for (it=client_list.begin(); it != client_list.end(); ++it) {
        if (0 == strcmp(it->username, msg.body)) {
            continue;
        }

        struct sockaddr_in peeraddr;
        memset(&peeraddr, 0, sizeof(struct sockaddr_in));

        peeraddr.sin_family = AF_INET;
        peeraddr.sin_port   = it->port;
        peeraddr.sin_addr.s_addr = it->ip;
        msg.cmd = htonl(S2C_SOMEONE_LOGOUT);

        if (sendto(sock, &msg, sizeof(MESSAGE), 0
                , (struct sockaddr *)&peeraddr
                , sizeof(sockaddr)) < 0) {
            perror("sendto");
        }
    }
}

void do_sendlist(int sock, MESSAGE &msg, struct sockaddr_in *cliaddr)
{
    printf("sending user list information to: %s <-> %s:%d\n"
            , msg.body
            , inet_ntoa(cliaddr->sin_addr)
            , ntohs(cliaddr->sin_port));     

    socklen_t socklen = sizeof(sockaddr);

    MESSAGE reply_msg; 
    memset(&reply_msg, 0, sizeof(MESSAGE));
    reply_msg.cmd = htonl(S2C_ONLINE_USER);
    sendto(sock, &reply_msg, sizeof(MESSAGE), 0
            , (struct sockaddr *)cliaddr
            , socklen);


    int count = htonl((int)client_list.size());
    //发送在线人数
    sendto(sock, &count, sizeof(int), 0
            , (struct sockaddr *)cliaddr, socklen);

    USER_LIST::iterator it;
    for (it=client_list.begin(); it != client_list.end(); ++it) {
        sendto(sock, &*it, sizeof(USER_INFO), 0
                , (struct sockaddr *)cliaddr, socklen);
    } // for it
}

int main(int argc, char *argv[])
{
    int listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (listenfd < 0) {
        ERR_EXIT("socket");
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(PORT);
    addr.sin_addr.s_addr    = htonl(INADDR_ANY);
    socklen_t addrlen       = sizeof(struct sockaddr_in);
    if (bind(listenfd, (struct sockaddr *)&addr, addrlen) < 0) {
        ERR_EXIT("bind");
    }

    do_srv(listenfd);

    return 0;
}
