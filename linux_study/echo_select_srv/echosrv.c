#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/select.h>

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

// recv MSG_PEEK 只是偷窥数据，并不会移走内核缓冲区的数据
ssize_t recv_peek(int sockfd, void *buf, size_t len)
{
    while (1) {
        int ret = recv(sockfd, buf, len, MSG_PEEK);
        if (-1 == ret && errno == EINTR) {
            continue;
        }
        return ret;
    } // while
}

ssize_t readline(int sockfd, void *buf, size_t maxline)
{
    int ret;
    int readlen;
    int left = maxline;
    char *tempbuf = buf;

    while (1) {
        ret = recv_peek(sockfd, tempbuf, left); 
        if (ret < 0) {
            return ret;
        } else if (ret == 0) {
            return ret;
        }

        readlen = ret;
        int i = 0;
        for (; i<readlen; ++i) {
            if (tempbuf[i] != '\n') {
                continue;
            } // if
            // 将'\n' 也读取
            ret = readn(sockfd, tempbuf, i+1);
            if (ret != i+1) {
                exit(EXIT_FAILURE);
            }
            return ret;
        } // for

        if (readlen > left) {
            ERR_EXIT("readnline");
        }

        left -= readlen;
        ret = readn(sockfd, tempbuf, readlen);
        if (ret != readlen) {
            ERR_EXIT("readn");
        }
        tempbuf += readlen;
    } // while
}

void do_service(int connfd)
{
    char recvbuf[1024] = {0};
    while (1) {
        memset(recvbuf, 0, sizeof(recvbuf));

        int ret = readline(connfd, recvbuf, sizeof(recvbuf));
        if (ret < 0) {
            break; 
        } else if (ret == 0) {
            printf("client quit.\n");
            break;
        }

        fputs(recvbuf, stdout);
        ret = writen(connfd, recvbuf, strlen(recvbuf));
        if (ret < 0) {
            ERR_EXIT("writen");
        }
    } // while
	close(connfd);
}

void handle_sigchld(int signalid)
{
    while (waitpid(-1, NULL, WNOHANG)) { ; }
}

void handle_sigint(int signalid)
{
    printf("server close\n");
    exit(0);
}

int main(void)
{
    // 忽略到子进程退出的消息
    /* signal(SIGCHLD, SIG_IGN); */
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, handle_sigchld);
    signal(SIGINT, handle_sigint);

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

    /*

    int connfd = 0;
    pid_t pid  = 0;
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
     
    */

    // 使用select
    fd_set allset;
    fd_set rset;
    FD_ZERO(&allset);
    FD_ZERO(&rset);
    FD_SET(listenfd, &allset);

    int client[FD_SETSIZE];
    for (int i=0; i<FD_SETSIZE; ++i) {
        client[i] = -1;
    }

    int maxfd = listenfd;
    int ready = 0;
    int conn  = 0;

    while (1) {
        // 每次都要重新设置，rset都会改变
        rset = allset;
        ready = select(maxfd+1, &rset, NULL, NULL, NULL);
        if (ready == -1) {
            if (errno == EINTR) {
                continue;
            } // if
        } else if (ready == 0) {    // 超时了
            continue;
        }
        
        if (FD_ISSET(listenfd, &rset)) {    // 产生了新的连接
            socklen = sizeof(clientaddr);
            conn = accept(listenfd, 
                          (struct sockaddr *)&clientaddr, &socklen); 
            if (conn == -1) {
                ERR_EXIT("accept");
            } // if

            printf("client ip:%s, port:%d\n"
                    , inet_ntoa(clientaddr.sin_addr)
                    , ntohs(clientaddr.sin_port));
            
            for (int i=0; i<FD_SETSIZE; ++i) {
                if (client[i] != -1) {
                    continue;
                } // if 
                
                client[i] = conn;
                FD_SET(conn, &allset);
                break;
            } // for

            maxfd = conn > maxfd ? conn : maxfd;

            if (--ready <= 0) {
                continue;
            } // if
        } // if 

        for (int i=0; i<FD_SETSIZE; ++i) {
            int connfd = client[i];
            if (connfd == -1) {
                continue;
            } 

            if (! FD_ISSET(connfd, &rset)) {
                continue;
            }
            
            // 有数据来了
            char recvbuf[1024] = {0};
            int ret = readline(connfd, recvbuf, sizeof(recvbuf));
            if (ret < 0) {
                ERR_EXIT("readline");
            } else if (ret == 0) {
                printf("client close\n");
                // 清空fd
                FD_CLR(connfd, &allset);
                
                client[i] = -1;

                close(connfd);
                // 所有有变化的fd已经处理完
                if (--ready <= 0) {
                    break;
                }
                continue;
            }
            fputs(recvbuf, stdout);
            writen(connfd, recvbuf, strlen(recvbuf));
            memset(recvbuf, 0, strlen(recvbuf));
            // 所有有变化的fd已经处理完
            if (--ready <= 0) {
                break;
            }
        } // for i

    } // while

    return 0;
}
