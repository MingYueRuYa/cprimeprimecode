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

void do_echo(int sockfd)
{
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};

    struct sockaddr_in localaddr;
    socklen_t socklen = sizeof(localaddr);
    
    // 必须在建立连接之后调用这个函数,
    // 获取本机连接之后的IP地址和port
    if (getsockname(sockfd, (struct sockaddr *)&localaddr, &socklen) < 0) {
        ERR_EXIT("getsockname");
    }
    printf("ip:%s, port:%d.\n"
            , inet_ntoa(localaddr.sin_addr)
            , ntohs(localaddr.sin_port));

    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        int ret = write(sockfd, sendbuf, strlen(sendbuf)); 
        if (ret < 0) {
            ERR_EXIT("writen");
        } 
        
        ret = read(sockfd, recvbuf, sizeof(recvbuf));
        if (ret < 0) {
            ERR_EXIT("readnline");
        } else if (ret == 0) {
            printf("server closed.\n");
        }

        fputs(recvbuf, stdout);
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }
    close(sockfd);
}

int main(void)
{
    int sock[5];
    int i = 0;
    // 测试僵尸进程，产生5个sock连接
    for (; i<1; ++i) {
        sock[i] = socket(PF_INET, SOCK_STREAM, 0);
        /* socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); */
        if (sock[i] < 0) {
            ERR_EXIT("socket");
        }

        struct sockaddr_in clientaddr;
        clientaddr.sin_family = AF_INET;
        clientaddr.sin_port   = htons(5188);
        clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
        /* servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); */
        /* inet_aton("127.0.0.1", servaddr.sin_addr); */
        
        socklen_t socklen = sizeof(clientaddr);
        if (connect(sock[i]
                    , (struct sockaddr *)&clientaddr
                    , socklen) < 0) {
            ERR_EXIT("connect");
        }
    }
    do_echo(sock[0]);
    return 0;
}
