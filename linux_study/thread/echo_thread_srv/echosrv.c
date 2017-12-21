#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "common.h"

void do_service(int connfd)
{
    char recvbuf[1024] = {0};
    while (1) {
        memset(recvbuf, 0, sizeof(recvbuf));

        int ret = read(connfd, recvbuf, sizeof(recvbuf));
        if (ret < 0) {
            break; 
        } else if (ret == 0) {
            printf("client quit.\n");
            break;
        }

        fputs(recvbuf, stdout);
        ret = write(connfd, recvbuf, strlen(recvbuf));
        if (ret < 0) {
            ERR_EXIT("writen");
        }
    } // while
}

void signal_sigchld(int signalid)
{
    while (waitpid(-1, NULL, WNOHANG)) { ; }
}

void *thread_routine(void *arg)
{
	if (NULL == arg) {
		return (void *)-1;
	}

	pthread_detach(pthread_self());
	printf("connfd:%d\n", *(int *)arg);
	do_service(*(int*)arg);
	printf("exit thread...\n");
	free((int *)arg);
	arg = NULL;
	return NULL;
}

int main(void)
{
    // 忽略到子进程退出的消息
    /* signal(SIGCHLD, SIG_IGN); */
    signal(SIGCHLD, signal_sigchld);
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
    while (1) {
        // 后面两个可以为NULL表示不需要连接过来的对方IP地址
        // 设置为NULL之后可以在调用getpeername获取对方的信息
        if ((connfd = accept(listenfd
                        , (struct sockaddr *)&clientaddr
                        , &socklen)) < 0) {
            ERR_EXIT("accept");
        }
        printf("ip=%s, port=%d.\n"
                , inet_ntoa(clientaddr.sin_addr)
                , ntohs(clientaddr.sin_port));

		//这种方式对跨平台更好
		int *fd = (int *)malloc(sizeof(int));
		*fd = connfd;
		pthread_t pid = -1;
		int ret = pthread_create(&pid, NULL, thread_routine, (void *)fd);
		if (0 != ret) {
			fprintf(stderr, "pthread_create:%s\n", strerror(ret));
			exit(EXIT_FAILURE);
		}
    } // while
    return 0;
}
