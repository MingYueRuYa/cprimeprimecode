/*****************************************************************************
**
**  Copyright (C) 2017 liushixiong@163.com
**  All rights reserved.
**
*****************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/types.h>        
#include <sys/socket.h>
#include <sys/epoll.h>  
#include <sys/stat.h>  
#include <arpa/inet.h>         
#include <netinet/in.h>

#include <vector>
#include <algorithm>

#include "common.h"

using std::cout;
using std::endl;
using std::vector;

typedef vector<struct epoll_event> EventList;

void SetupSignal()
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

int main(int argc, char *argv[])
{
	SetupSignal();

    int idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);

	int listenfd = socket(AF_INET
                            , SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC
                            , IPPROTO_TCP);
	if (listenfd == -1) {
		ERR_EXIT("socket");	
	}

	int on = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
		ERR_EXIT("setsockopt");	
	}

	struct sockaddr_in serveradd;
	memset(&serveradd, 0, sizeof(serveradd));
	serveradd.sin_family 	= AF_INET;
	serveradd.sin_port		= htons(5188);
	serveradd.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(listenfd, (struct sockaddr *)&serveradd, sizeof(serveradd)) < 0) {
		ERR_EXIT("bind");	
	}
	if (listen(listenfd, SOMAXCONN) < 0 ) {
		ERR_EXIT("listen");	
	}

    vector<int> clients;
    int epollfd = epoll_create1(EPOLL_CLOEXEC);

    struct epoll_event event;
    event.data.fd   = listenfd;
    event.events    = EPOLLIN;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event);

    EventList eventlist(16);
    struct sockaddr_in peeraddr;
    socklen_t peerlen;

    int nready = 0;
	while (1) {
        nready = epoll_wait(epollfd, &*(eventlist.begin())
                            , static_cast<int>(eventlist.size())
                            , -1);
        if (-1 == nready) {
            if (errno == EINTR) {
                continue;
            } else {
                ERR_EXIT("epoll_wait");
            }
        }

        if (0 == nready) {
            continue;
        }

        if ((size_t)nready == eventlist.size()) {
            eventlist.resize(eventlist.size()*2);
        }

        for (int i=0; i<nready; ++i) {
            if (eventlist[i].data.fd == listenfd) {
                peerlen = sizeof(peeraddr);
                int connfd = accept4(eventlist[0].data.fd
                                    , (struct sockaddr *)&peeraddr
                                    , &peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
                if (-1 == connfd) {
                    if (EMFILE == errno) {
                        close(idlefd);
                        idlefd = accept(listenfd, NULL, NULL);
                        close(idlefd);
                        idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
                        continue;
                    } else {
                        ERR_EXIT("accept4");
                    }
                } // if connd
                cout << "ip:" << inet_ntoa(peeraddr.sin_addr)
                     << " port:" << ntohs(peeraddr.sin_port)
                     << endl;
                clients.push_back(connfd);
                event.data.fd   = connfd;
                event.events    = EPOLLIN;
                eventlist.push_back(event);
                epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event);
            } else if (eventlist[i].events && EPOLLIN) { 
                int connfd = eventlist[i].data.fd;
                if (connfd < 0) {
                    continue;
                }

               char recvbuf[1024] = {0};
               int readlen = read(connfd, recvbuf, sizeof(recvbuf));
               if (readlen < 0) {
                    ERR_EXIT("read");
               } else if (0 == readlen) {
                    cout << "client close" << endl;
                    close(connfd); 
                    event = eventlist[i];
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, connfd, &event);
                    clients.erase(std::remove(clients.begin()
                                            , clients.end()
                                            , connfd)
                                    , clients.end());
                    continue;
               } else {
                   cout << recvbuf;
                   write(connfd, recvbuf, strlen(recvbuf));
                   memset(recvbuf, 0, sizeof(recvbuf));
               } // if readlen
            } // if 
        } // for i
    }
	return 0;
}
