#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <poll.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

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

void do_echo(int sockfd)
{
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};

    // fd_set fd_read_set;
    // FD_ZERO(&fd_read_set);

	struct pollfd fdarray[2];

    int ready;
    //不要使用STDFILE_IN，因为为0，重定向之后就不是0
    int fd_stdin = fileno(stdin);   
    int maxfd = sockfd > fd_stdin ? sockfd : fd_stdin;

	fdarray[0].fd = fd_stdin;
	fdarray[0].events = POLLIN;
	fdarray[1].fd = sockfd;
	fdarray[1].events = POLLIN;

    while (1) {
		// -1表示不设置超时时间
        ready = poll(fdarray, 3, -1);
        if (ready < -1) {
            if (errno == EINTR) {
                continue;
            }
            ERR_EXIT("select"); 
        } else if (ready == 0) {    //返回值为0表示超时
            continue;
        }

        if (fdarray[1].revents & POLLIN) {
            int ret = readline(fdarray[1].fd, recvbuf, sizeof(recvbuf));
            if (ret == -1) {
                ERR_EXIT("readline");
            } else if (ret == 0) {
                printf("server closed\n");
                break;
            } // if
            fputs(recvbuf, stdout);
        } // if
        
        if (fdarray[0].revents & POLLIN) {
            if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) {
                break;
            }
            int ret = writen(fdarray[1].fd, sendbuf, strlen(sendbuf));
            if (ret == -1) {
                ERR_EXIT("writen");
            } else if (ret == 0) {
                printf("server closed\n");
                break;
            }
        } // if

        memset(sendbuf, 0, strlen(sendbuf));
        memset(recvbuf, 0, strlen(recvbuf));

    } // while
    close(sockfd);
}

void handle_sigpipe(int signalnum)
{
	printf("signal num:%d.\n", signalnum);
}

void handle_sigint(int signalnum)
{
	printf("client quit\n");
    exit(0);
}

void do_testsockmax()
{
	setfdcount(1024);
	int currentfd = 0;
	while (1) {
		int sock = socket(PF_INET, SOCK_STREAM, 0);
		/* socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); */
		if (sock < 0) {
			sleep(10);
			ERR_EXIT("socket");
		}

		printf("current fd:%d\n", currentfd++);

		struct sockaddr_in clientaddr;
		clientaddr.sin_family = AF_INET;
		clientaddr.sin_port   = htons(5188);
		clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

		socklen_t socklen = sizeof(clientaddr);
		if (connect(sock
					, (struct sockaddr *)&clientaddr
					, socklen) < 0) {
			ERR_EXIT("connect");
		}
	}
}

int main(void)
{
	/* signal(SIGPIPE, handle_sigpipe); */
	signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, handle_sigint);
	
	/* test server sock limit */
	// do_testsockmax();

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    /* socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); */
    if (sock < 0) {
        ERR_EXIT("socket");
    }

    struct sockaddr_in clientaddr;
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port   = htons(5188);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    /* servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); */
    /* inet_aton("127.0.0.1", servaddr.sin_addr); */
    
    socklen_t socklen = sizeof(clientaddr);
    if (connect(sock
                , (struct sockaddr *)&clientaddr
                , socklen) < 0) {
        ERR_EXIT("connect");
    }
    do_echo(sock);
    return 0;
}
