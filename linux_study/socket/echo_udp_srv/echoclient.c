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

void do_client(int sockfd)
{
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    while (1) {
       if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) {
            break;
       } 
       if (send(sockfd, sendbuf, strlen(sendbuf), 0) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                ERR_EXIT("send");
            }
       }

       if (recv(sockfd, recvbuf, sizeof(recvbuf), 0) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                ERR_EXIT("send");
            }
       } else {
            fputs(recvbuf, stdout);
       }
       memset(sendbuf, 0, strlen(sendbuf));
       memset(recvbuf, 0, strlen(recvbuf));
    }
    close(sockfd);
}

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        ERR_EXIT("socket");        
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP);
    socklen_t len        = sizeof(struct sockaddr_in);
    int ret = connect(sockfd, (struct sockaddr *)&addr, len);
    if (ret < 0) {
        ERR_EXIT("socket");        
    }

    do_client(sockfd);

    return 0;
}
