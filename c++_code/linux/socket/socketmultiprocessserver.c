/*
 * multi process server
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

// truct sockaddr_in {
//                sa_family_t    sin_family; /* address family: AF_INET */
//                in_port_t      sin_port;   /* port in network byte order */
//			    struct in_addr sin_addr;   /* internet address */
//				};
// struct in_addr {
//	                uint32_t  s_addr;     /* address in network byte order */
//				};
int main(void)
{
	unsigned sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		perror("socket failed.");
		exit(-1);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8001);
	//addr.sin_addr.s_addr = inet_addr("192.168.1.113");
	addr.sin_addr.s_addr = inet_addr("192.168.0.110");
	if (-1 == bind(sockfd, (struct sockaddr *)&addr,sizeof(addr))) {
		perror("socket bind failed.");
		exit(-1);
	}
	if (-1 == listen(sockfd, SOMAXCONN)) { //被动socket
		perror("socket listen failed.");
		exit(-1);
	}
	struct sockaddr_in connsockaddr;
	socklen_t connsockaddrlen = sizeof(connsockaddr);
	while (1) {
		int connsockfd = accept(sockfd, (struct sockaddr *)&connsockaddr, &connsockaddrlen);
		if (-1 == connsockfd) {
			perror("socket accept failed.");
			exit(-1);
		}
		pid_t pid = fork();
		if (-1 == pid) {
			perror("Create children process failed.");
			exit(-1);
		}
		//child process
		else if (0 == pid) {
			//close listen socket fd
			close(sockfd);
			char recbuf[1024] = {0};
			while (1) {
				ssize_t reclen = read(connsockfd, recbuf, sizeof(recbuf));
				if (-1 == reclen) {
					perror("socket read failed.");
					exit(-1);
				}
				ssize_t sendlen = write(connsockfd, recbuf, strlen(recbuf));
				if (-1 == sendlen) {
					perror("socket write failed.");
					exit(-1);
				}
				fputs(recbuf, stdout);
				memset(recbuf, 0, sizeof(recbuf));
			}
		}
		//parent process
		else if (pid > 0) {
			//close connect socket fd.
			close(connsockfd);
			printf("peer socket ipaddress: %s, port is %d.\n", inet_ntoa(connsockaddr.sin_addr), ntohs(connsockaddr.sin_port));
		}
	}
	//close(connsockfd);
	wait();
	close(sockfd);	
	return 0;
}
