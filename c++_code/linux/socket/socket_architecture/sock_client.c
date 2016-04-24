
#ifndef sock_client_h
#define sock_client_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "sockutil.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8001
#define RECV_BUFFER_SIZE 1024

int main(void)
{
	void *handle = NULL;	
	int connfd = 0;
	char *data = "linux is very good!";

	int ret = sckClient_init(&handle, 30, 30, 30, 10);
	if (0 != ret) {
		printf("Init error code %d.\n", ret);
		return ret;
	}

	ret = sckClient_getconn(handle, SERVER_IP, SERVER_PORT, &connfd);
	if (0 != ret) {
		printf("Getconn error code %d.\n", ret);
		perror("Getconn error");
		return ret;
	}

	ret = sckClient_send(handle, connfd, (unsigned char *)data, strlen(data));
	if (0 != ret) {
		printf("Send error code %d.\n", ret);
		perror("Send error");
		return ret;
	}
	//sckClient_recv(void *pHandle, int connfd, unsigned char *outdata, int datalen)
	unsigned char buffer[RECV_BUFFER_SIZE] = {0};
	ret = sckClient_recv(handle, connfd, buffer, sizeof(buffer));
	if (0 != ret) {
		printf("Recvie error code %d.\n", ret);
		perror("Recvie error:\n");
		return ret;
	}
	printf("recv....\n");
	printf("%s", buffer);

	sckClient_closeconn(&connfd);

	sckClient_destory(handle);

	return 0;
}

#endif //sock_client_h
