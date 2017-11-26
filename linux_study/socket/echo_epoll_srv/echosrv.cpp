#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/epoll.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <vector>
#include <algorithm>

#include "common.h"

#define MAX_FD_SIZE 2048

typedef std::vector<struct epoll_event> EventList;

int activate_nonblock(int fd)
{
	int ret 	= -1;	
	int flags 	= fcntl(fd, F_GETFL);
	if (flags < -1) {
		ERR_EXIT("fcntl");
	}

	flags 	|= O_NONBLOCK;
	ret 	= fcntl(fd, F_SETFL, flags);
	if (flags < -1) {
		ERR_EXIT("fcntl");
	}
	return ret;
}

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

	// setfdcount(MAX_FD_SIZE);

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

    int ready = 0;
    int conn  = 0;

	std::vector<int> clients;
	int epollfd = epoll_create1(EPOLL_CLOEXEC);
	if (epollfd < 0) {
		ERR_EXIT("epoll_create1");
	}

	struct epoll_event event;
	event.data.fd = listenfd;
	event.events  = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);
	
	EventList events(16);
	
    while (1) {
		ready = epoll_wait(epollfd, &*events.begin(), events.size(), -1);
        if (ready == -1) {
            if (errno == EINTR) {
                continue;
            } else {
				ERR_EXIT("epoll_wait");
			}
        } else if (ready == 0) {    // 超时了
            continue;
        }

		if (ready == static_cast<int>(events.size())) {
			events.resize(events.size()*2);
		}

		for (int i=0; i<ready; ++i) {
			if (events[i].data.fd == listenfd) {
				socklen = sizeof(clientaddr);
				conn = accept(listenfd, 
							  (struct sockaddr *)&clientaddr, &socklen); 
				if (conn == -1) {
					ERR_EXIT("accept");
				} // if

				printf("client ip:%s, port:%d\n"
						, inet_ntoa(clientaddr.sin_addr)
						, ntohs(clientaddr.sin_port));

				clients.push_back(conn);	
				activate_nonblock(conn);
				
				event.data.fd	= conn;
				event.events	= EPOLLIN | EPOLLET;
				epoll_ctl(epollfd, EPOLL_CTL_ADD, conn, &event);
			}
			else if (events[i].events & EPOLLIN) {
				conn = events[i].data.fd;
				if (conn < 0) {
					continue;
				}
				
				char recvbuf[1024] = {0};
				int ret = read(conn, recvbuf, sizeof(recvbuf));
				if (ret < 0) {
					ERR_EXIT("read");	
				} else if (ret == 0) {
					printf("client close\n");
					close(conn);
					event = events[i];
					epoll_ctl(epollfd, EPOLL_CTL_DEL, conn, &event);
					clients.erase(std::remove(clients.begin(),
								clients.end(), conn), clients.end());
				}
				else {
					fputs(recvbuf, stdout);
					write(conn, recvbuf, strlen(recvbuf));
				} // if ret
			}
		} // for i
    } // while

    return 0;
}
