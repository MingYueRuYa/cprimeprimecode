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

int main(void)
{
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    /* socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); */
    if (sockfd < 0) {
        ERR_EXIT("socket");
    }

    struct sockaddr_in clientaddr;
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port   = htons(5188);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    /* servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); */
    /* inet_aton("127.0.0.1", servaddr.sin_addr); */
    
    socklen_t socklen = sizeof(clientaddr);
    if (connect(sockfd, (struct sockaddr *)&clientaddr, socklen) < 0) {
        ERR_EXIT("connect");
    }

    packet sendbuf;
    packet recvbuf;
    memset(&sendbuf, 0, sizeof(sendbuf));
    memset(&recvbuf, 0, sizeof(recvbuf));

    while (fgets(sendbuf.buff, sizeof(sendbuf.buff), stdin) != NULL) {
        sendbuf.len = htonl(strlen(sendbuf.buff));
        if (writen(sockfd, 
                   &sendbuf, 
                   4+strlen(sendbuf.buff)) < 0) {
            break;
        }

        // 先读包长
        int ret = read(sockfd, &recvbuf.len, 4);
        if (ret < 0) {
            break;
        } 

        int packet_content_length = ntohl(recvbuf.len);
        if (read(sockfd, recvbuf.buff, packet_content_length) == 0) {
            break;
        }
        fputs(recvbuf.buff, stdout);

        memset(&sendbuf, 0, sizeof(sendbuf));
        memset(&recvbuf, 0, sizeof(recvbuf));
    }
    close(sockfd);
    return 0;
}
