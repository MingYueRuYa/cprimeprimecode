#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

#define ERR_EIXT(message)   \
    do {    \
        perror(message);    \
        exit(EXIT_FAILURE);  \
    } while(0) 

#define PORT 5188

#define SOCK_PATH "/tmp/sock_file"

void do_echo(int connfd)
{
    char recvbuf[1024] = {0};

    while (1) {
        int ret = read(connfd, recvbuf, sizeof(recvbuf));
        if (ret < 0 && errno == EINTR) {
            continue; 
        } else if (ret < 0) {
            ERR_EIXT("read");
        }

        ret = write(connfd, recvbuf, strlen(recvbuf));
        if (ret < 0 ) {
            ERR_EIXT("write");
        }
        fputs(recvbuf, stdout);
        memset(recvbuf, 0, strlen(recvbuf));
    }
}

int main(int argc, char *argv[])
{
    // 每次启动时都先unlink删除套接字文件
    unlink(SOCK_PATH);
    
    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (sockfd < 0) {
        ERR_EIXT("socket");
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);

    // unix域协议不需要设置地址重复利用选项
    socklen_t socklen = sizeof(addr);
    if (bind(sockfd, (struct sockaddr *)&addr, socklen) < 0) {
        ERR_EIXT("bind");
    }

    if (listen(sockfd, SOMAXCONN) < 0) {
        ERR_EIXT("listen");
    }

    while (1) {
       struct sockaddr_in peerclient;
       memset(&peerclient, 0, sizeof(peerclient));
       socklen_t socklen = sizeof(peerclient);
       int connfd = 0;
       if ((connfd = accept(sockfd
                   , (struct sockaddr *)&peerclient
                   , &socklen)) < 0) {
            ERR_EIXT("accept");
       }

       pid_t child_pid = fork();
       if (child_pid < 0) {
            ERR_EIXT("fork");
       } else if (child_pid == 0) { //child process
            close(sockfd);
            do_echo(connfd);
            exit(EXIT_SUCCESS);
       } else {
            close(connfd);
       }
    } 

    close(sockfd);

    return 0;
}
