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

#define ERR_EXIT(msg)   \
    do  \
    {   \
        perror(msg);    \
        exit(EXIT_FAILURE);  \
    } while (0)

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

    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        if (write(sockfd, sendbuf, strlen(sendbuf)) == 0) {
            //TODO 退出
            break;
        }

        //服务器退出
        if (read(sockfd, recvbuf, sizeof(recvbuf)) == 0) {
            break;
        }
        fputs(recvbuf, stdout);
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }
    close(sockfd);
    return 0;
}
