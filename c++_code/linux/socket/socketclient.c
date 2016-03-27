#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd) {
		perror("socket failed.");
		exit(-1);
	}
	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(8001);
	sockaddr.sin_addr.s_addr = inet_addr("192.168.1.113");
	if ( -1 == connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr))) {
		perror("socket connect failed.");
		exit(-1);
	}
	char sendbuf[1024] = {0};
	char recbuf[1024] = {0};
	while (NULL != fgets(sendbuf, sizeof(sendbuf),stdin)) {
		ssize_t sendlen = write(sockfd, sendbuf, strlen(sendbuf));	
		if (-1 == sendlen) {
			perror("socket write failed.");
			exit(-1);
		}
		ssize_t reclen = read(sockfd, recbuf, sizeof(recbuf));
		if (-1 == reclen) {
			perror("socket read failed.");
			exit(-1);
		}
		fputs(recbuf, stdout);
		memset(recbuf, 0, sizeof(recbuf));
		memset(sendbuf, 0, sizeof(sendbuf));
	}
	return 0;
}
