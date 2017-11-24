#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "common.h"

ssize_t readn(int fd, void *buff, ssize_t count)
{
    int     left = count;
    ssize_t already_read = 0;
    char *tempbuf = buff;
    while (left > 0) {
        already_read = read(fd, tempbuf, left);
        if (already_read < 0) {
            if (errno == EINTR) {   // 信号中断
                continue;
            } else {
                return -1;
            }
        } else if (already_read == 0) {
           // 剩余未读字节数
           return count-already_read; 
        }

        tempbuf += already_read;
        left    -= already_read;
    } // while
    return count;
}

ssize_t writen(int fd, void *buff, ssize_t count)
{
    int     left            = count;
    ssize_t already_write   = 0;
    char *tempbuf = buff;
    while (left > 0) {
        already_write = write(fd, tempbuf, left);
        if (already_write < 0) {
            if (errno == EINTR) {   // 信号中断
                continue;
            } else {
                return -1;
            }
        } else if (already_write == 0) {
            continue;
        }

        tempbuf += already_write;
        left    -= already_write;
    } // while
    return count;
}

void do_service(int connfd)
{
    // char recvbuf[1024] = {0};
    packet recvbuf;
    int pack_len_size = sizeof(recvbuf.len);
    while (1) {
        memset(&recvbuf, 0, sizeof(recvbuf));
        // 1.先读包长
        int ret = readn(connfd, &recvbuf.len, pack_len_size);
        if (ret < 0) {
            ERR_EXIT("read");
        } else if (ret < pack_len_size) {
            printf("client quit.\n");
            break;
        }

        int pack_content_length = ntohl(recvbuf.len); 
        ret = readn(connfd, recvbuf.buff, pack_content_length);
        if (ret < 0) {
            ERR_EXIT("read");
        } else if (ret == 0) {
            printf("client quit.\n");
            break;
        }

        fputs(recvbuf.buff, stdout);

        if (writen(connfd, &recvbuf, 4+pack_content_length) < 0) {
            printf("write error.\n");
            exit(EXIT_FAILURE);
        }
    } // while
}

int main(void)
{
    //socket
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    /* socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); */
    if (listenfd < 0) {
        ERR_EXIT("socket");
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    /* servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); */
    /* inet_aton("127.0.0.1", servaddr.sin_addr); */

    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, 
                    SO_REUSEADDR, &on, sizeof(on)) < 0) {
        ERR_EXIT("setsockopt");
    }

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT("bind");
    }

    if (listen(listenfd, SOMAXCONN) < 0) {
        ERR_EXIT("listen");
    }
    
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(clientaddr));
    socklen_t socklen = sizeof(clientaddr);

    int connfd = 0;
    pid_t pid  = 0;
    while (1) {
        if ((connfd = accept(listenfd
                        , (struct sockaddr *)&clientaddr, &socklen)) < 0) {
            ERR_EXIT("accept");
        }
        printf("ip=%s, port=%d.\n"
                , inet_ntoa(clientaddr.sin_addr)
                , ntohs(clientaddr.sin_port));
        pid = fork();
        if (pid == -1) {
            ERR_EXIT("fork"); 
        } else if (pid == 0) { // child process
            close(listenfd);    // 不需要监听listenfd
            do_service(connfd);
            exit(EXIT_SUCCESS);
        } else {
            close(connfd);  // 不需要监听connfd
        } // if pid
    } // while
    return 0;
}
