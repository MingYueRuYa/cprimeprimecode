#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>          /* See NOTES */
#include <sys/stat.h>
#include <netinet/in.h>

#include <vector>

#include "common.h"

using std::cout;
using std::endl;
using std::vector;

typedef vector<struct pollfd> PollFdList;

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

	struct pollfd pfd;
	pfd.fd 		= listenfd;
	pfd.events 	= POLLIN;

	PollFdList pollfds;
	pollfds.push_back(pfd);

	struct sockaddr_in peeraddr;
	socklen_t peerlen;

	int readfd = 0;
	while (1) {
		readfd = poll(&*pollfds.begin(), pollfds.size(), -1);
		if (readfd == -1) {
			if (EINTR == errno) {
				continue;
            } else if (EMFILE == errno) {   // 达到最大文件描述符限制
                close(idlefd);  // 先关闭原先事先准备的空闲描述符
                idlefd = accept(listenfd, NULL, NULL);  // 接受一个请求
                close(idlefd);  // 立即将这个新的请求描述符关闭
                // 再打开空闲描述符，以便下次在替换新的描述符
                idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
			} else {
				ERR_EXIT("poll");
			}
		}

		if (readfd == 0) {
			continue;
		}

		if (pollfds[0].revents & POLLIN) {	//新的套接字
			peerlen = sizeof(peeraddr);
			int connfd = accept4(pollfds[0].fd, (struct sockaddr *)&peeraddr
									, &peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);	
			if (connfd == -1) {
				ERR_EXIT("accept4");
			}

			struct pollfd pfd;
			pfd.fd 		= connfd;	
			pfd.events 	= POLLIN;
			pollfds.push_back(pfd);
			--readfd;
			cout << "ip:" << inet_ntoa(peeraddr.sin_addr)
				 << " port:" << ntohs(peeraddr.sin_port)
				 << " count:" << pollfds.size() << endl;
		}

		for (PollFdList::iterator ibeg = pollfds.begin()+1;
			   	ibeg != pollfds.end() && readfd > 0; ++ibeg) {
			if ((*ibeg).revents & POLLIN) {
				--readfd;
				char buf[1024] = {0};
				int readlen = read((*ibeg).fd, buf, sizeof(buf));
				if (readlen < 0) {	// 这里一个连接读数据出错了，不应该退出
					ERR_EXIT("read");
				} else if (readlen == 0) {
					cout << "client close" << endl;
					close((*ibeg).fd);
					ibeg = pollfds.erase(ibeg);
					--ibeg;
				} else {
					cout << buf;
					write((*ibeg).fd, buf, strlen(buf));
				}
			} // if
		} // for
	}

	return 0;
}
