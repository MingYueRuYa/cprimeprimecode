/*
 * single process come true multi socket by select management
 * 使用单进程实现监听多个描述符
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR_EXIT(m) \
	do { \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

#define SERVER_IP "192.168.1.113"
#define SERVER_PORT 8001

//#define SOCKET_MAX_SIZE 1024

void handle_sigchld(int pSignalNumber)
{
	while (waitpid(-1, NULL, WNOHANG) > 0) {
		;
	}
}

void handle_sigpipe(int pSignalNumber)
{
	printf("recv sigpipe signal.\n");
}

int main(void)
{
	signal(SIGCHLD, handle_sigchld);
	signal(SIGPIPE, handle_sigpipe);
	
	int sockfd = 0;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		ERR_EXIT("socket error:");
	}

	struct sockaddr_in serveraddr;	
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serveraddr.sin_port = htons(SERVER_PORT);
	int optval = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval)) < 0) {
		ERR_EXIT("setsockopt errro:");
	}
	if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
		ERR_EXIT("bind error:");
	}
	if (listen(sockfd, SOMAXCONN)< 0) {
		ERR_EXIT("listen error:");
	}
	int client[FD_SETSIZE]; 
	int maxi = 0; //最大的不空闲描述符
	int i = 0;
	for (; i < FD_SETSIZE; ++i) {
		client[i] = -1;
	}
	
	int readynumber = 0;
	int maxfd = sockfd;
	fd_set rset;
	fd_set allset;
	FD_ZERO(&rset);
	FD_ZERO(&allset);
	FD_SET(sockfd, &allset);

	struct sockaddr_in peersockaddr;
	socklen_t socklen;
	int connfd;
	while (1) {
		rset = allset;
		readynumber = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (-1 == readynumber) {
			if (errno == EINTR) {
				continue;
			}
			ERR_EXIT("select error:");
		}
		else if (0 == readynumber) {
			continue;
		}
		if (FD_ISSET(sockfd, &rset)) { //already client connected.
			connfd = accept(sockfd, (struct sockaddr *)&peersockaddr, &socklen);	
			if (connfd <= 0) {
				if (errno == EINTR) {
					continue;
				}
				ERR_EXIT("accept error:");
			}
			for (i = 0; i < FD_SETSIZE; ++i) {
				if (client[i] < 0) {
					client[i] = connfd;
					if (i > maxi) {
						maxi = i;
					}
					break;
				}
			}
			if (i == FD_SETSIZE) {
				fprintf(stderr, "too many client.\n");	
				exit(EXIT_FAILURE);
			}
			printf("client ip %s, port %d.\n", inet_ntoa(peersockaddr.sin_addr), ntohs(peersockaddr.sin_port));
			FD_SET(connfd, &allset); //add new fd to allset
			if (connfd > maxfd) { //维护最大描述符
				maxfd = connfd;	
			}
			if (--readynumber <= 0) {
				continue;
			}
		}
		for (i = 0; i <= maxi; ++i) { //检测到有文件描述符的可读
			connfd = client[i];	 //当前的描述符
			if (-1 == connfd) {
				continue;
			}
			if (FD_ISSET(connfd, &rset)) { //检测到可读
				char recvbuff[1024]	 = {0};
				int recvlen = read(connfd, recvbuff, sizeof(recvbuff));
				if (-1 == recvlen) {
					ERR_EXIT("read error:");
				}
				else if (0 == recvlen) { //对方关闭连接
					printf("client closed.\n");
					client[i] = -1;
					FD_CLR(connfd, &allset); //从集合中清除
					close(connfd);
				}
				else {
					fputs(recvbuff, stdout);	
					if (write(connfd, recvbuff, strlen(recvbuff)) != strlen(recvbuff)) {
						ERR_EXIT("write error:");
					}

				}
				if (--readynumber <= 0) {
					break;
				}
			}	
		}
	}	
	return 0;
}
