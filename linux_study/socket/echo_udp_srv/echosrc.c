#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR_EXIT(msg)   \
    do {    \
        perror(msg);    \
        exit(EXIT_FAILURE);  \
    } while(0)

#define PORT    5188
#define IP      "127.0.0.1"

void do_srv(int sockfd)
{
    char recvbuf[1024] = {0};
    
    struct sockaddr_in peeraddr;
    socklen_t len;

    while (1) {
        len = sizeof(peeraddr);
        int ret = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0
                , (struct sockaddr *)&peeraddr, &len);
        printf("ip:%s, port:%d\n", inet_ntoa(peeraddr.sin_addr)
                                 , ntohs(peeraddr.sin_port));
        if (ret < 0 ) {
            if (errno == EINTR) {
                continue;
            } else {
                ERR_EXIT("recvfrom");
            }
        } else if (ret > 0) {
            ret = sendto(sockfd, recvbuf, strlen(recvbuf), 0
                , (struct sockaddr *)&peeraddr, len);
            if (ret == -1) {
                if (errno == EINTR) {
                    continue;
                } else {
                    ERR_EXIT("sendto");
                }
            } else {
                fputs(recvbuf, stdout);
            } // if
        } // if
        memset(recvbuf, 0, strlen(recvbuf)); 
    } // while 
    close(sockfd);
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
