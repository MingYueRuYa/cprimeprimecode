#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>

#define PORT 8001
#define SERVER_IP "127.0.0.1"

int global_sockfd;

void SigHandler(int pSignal, siginfo_t *pSiginfo, void *pVoid)
{
	if (SIGINT == pSignal) {
		close(global_sockfd);
		printf("Close client.\n");
		exit(0);
	}
}

int main(void)
{
	signal(SIGPIPE, SIG_IGN);
	struct sigaction act;
	act.sa_sigaction = SigHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	if ((global_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Connect error:\n");
		exit(-1);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if (connect(global_sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0 ) {
		perror("Connect error:\n");
		exit(-1);
	}
	char sendbuf[1024] = {0};
	char recvbuf[1024] = {0};
	int fd_stdin = fileno(stdin);
	fd_set read_fd_set;
	FD_ZERO(&read_fd_set);

	int max_fd = global_sockfd > fd_stdin ? global_sockfd : fd_stdin;
	struct timeval time_val;
	time_val.tv_sec = 30;
	time_val.tv_usec = 0;
	while (1) {
		/*FD_SET need to repeat to set fd.*/
		FD_SET(fd_stdin, &read_fd_set);
		FD_SET(global_sockfd, &read_fd_set);
		int retval = select(max_fd + 1, &read_fd_set, NULL, NULL, &time_val);
		if (-1 == retval) {
			if (EINTR == errno) {
				continue;
			}
			close(global_sockfd);
			exit(-1);
		}
		else if (0 == retval) {
			printf("time expired.\n");
		}
		else {
			printf("retval %d, max fd %d.\n", retval, max_fd);
			if (FD_ISSET(fd_stdin, &read_fd_set)) {
				if (NULL == fgets(sendbuf, sizeof(sendbuf), stdin)) {
					close(global_sockfd);
					exit(-1);
				}
				int writelen = write(global_sockfd, sendbuf, strlen(sendbuf));
				if (-1 == writelen) {
					if (EINTR == errno) {
						continue;
					}
					close(global_sockfd);
					exit(-1);
				}
			}
			else if (FD_ISSET(global_sockfd, &read_fd_set)) {
				printf("sockfd changed.\n");
				int readlen = read(global_sockfd, recvbuf, sizeof(recvbuf));
				if (0 == readlen) {
					printf("Server close.\n");
					close(global_sockfd);
				}
				else if (-1 == readlen) {
					if (EINTR == errno) { //maybe interupte by signal
						continue;
					}
					perror("Write error:\n");
					return -1;
				}
				else {
					printf("%s", recvbuf);
				}
			}
		}
		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
	}
	return 0;
}
