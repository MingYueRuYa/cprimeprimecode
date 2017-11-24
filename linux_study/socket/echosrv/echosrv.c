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

void do_service(int connfd)
{
    char recvbuf[1024] = {0};
    while (1) {
        int ret = read(connfd, recvbuf, sizeof(recvbuf));
        if (ret == 0) {
            printf("clinet quit.\n");
            break;
        }
        fputs(recvbuf, stdout);
        if (write(connfd, recvbuf, ret) < 0) {
            printf("write error.\n");
            exit(EXIT_FAILURE);
        }
        memset(recvbuf, 0, sizeof(recvbuf));
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
