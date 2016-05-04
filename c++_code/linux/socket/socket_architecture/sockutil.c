#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/select.h>
#include <sys/time.h>

#include "sockutil.h"

#define MAX_PORT 65535

typedef struct socket_handle{
	int sock_array[100];
	int arraynum;
	int sockfd;
	int conntime;
	int sendtime;
	int recvtime;
}SOCKET_HANDLE;

int sckClient_init(void **pHandle, int connecttime, int sendtime, int recvtime, int nConNum)
{
	int ret = 0;
	if (NULL == pHandle || connecttime < 0 || sendtime < 0 || recvtime < 0 || nConNum < 0) {
		ret = SOCKET_ERROR_PARAMETER;
		return ret;
	}
	SOCKET_HANDLE *tmp = (SOCKET_HANDLE *)malloc(sizeof(SOCKET_HANDLE));
	if (NULL == pHandle) {
		ret = SOCKET_ERROR_MALLOC;
		return ret;
	}
	tmp->conntime = connecttime;
	tmp->sendtime = sendtime;
	tmp->recvtime = recvtime;
	tmp->arraynum = nConNum;
	*pHandle = tmp;
	return ret;
}

/*
 * set file discript is nonblock
 * */
static int activate_nonblock(int pFileDiscripte)
{
	int ret = 0;	
	int flags = fcntl(pFileDiscripte, F_GETFL);
	if (-1 == flags) {
		ret = flags;
		return ret;
	}
	
	flags |= O_NONBLOCK;
	ret = fcntl(pFileDiscripte, F_SETFL, flags);
	if (-1 == ret) {
		return ret;
	}
	return ret;
}

/*
 * set file discript is block
 * */
static int deactivate_nonblock(int pFileDiscripte)
{
	int ret = 0;	
	int flags = fcntl(pFileDiscripte, F_GETFL);
	if (-1 == flags)  {
		ret = flags;
		return ret;
	}
	
	flags &= ~O_NONBLOCK;
	ret = fcntl(pFileDiscripte, F_SETFL, flags);
	if (-1 == ret) {
		return ret;
	}
	return ret;
}

static int connect_timeout(int sockfd, struct sockaddr *addr, unsigned int conntime)
{
	int ret = 0;
	socklen_t socklen = sizeof(*addr);
	if (conntime > 0) {
		//set sockfd is not block status.
		activate_nonblock(sockfd);
	}
	ret = connect(sockfd, addr, socklen);	
	if (ret < 0 && errno == EINPROGRESS) { //this is explain connect is solving.
		fd_set connect_fdset;	
		struct timeval timeout;
		FD_ZERO(&connect_fdset);
		FD_SET(sockfd, &connect_fdset);
		timeout.tv_sec = conntime;
		timeout.tv_usec = 0;
		do {
			//once connect server, socket could write to server, so connect_fd set to writefds.
			ret = select(sockfd + 1, NULL, &connect_fdset, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);

		if (0 == ret) {
			ret = -1;
			errno = ETIMEDOUT;
		}
		else if (ret < 0) {
			ret = -1;
		}
		else if (1 == ret) {
			//if ret equal to 1, has two case.One is connect successful, Other is socket error.	
			//if had occur error, error info not save to errno variable.so we should call getsockopt function to get error info.
			int err = 0;
			socklen_t len = sizeof(err);
			int sockoptret = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &err, &len);
			if (-1 == sockoptret) {
				ret = -1;
			}
			else if (0 == sockoptret) {
				ret = 0;
			}
			else {
				errno = sockoptret;
				ret = -1;
			}
		}
	}
	if (conntime > 0) {
		deactivate_nonblock(sockfd);
	}
	return ret;
}

int sckClient_getconn(void *pHandle, char *ip, unsigned int port, int *confd)
{
	if (NULL == pHandle || NULL == ip || port > MAX_PORT || NULL == confd) {
		return SOCKET_ERROR_PARAMETER;
	}
	SOCKET_HANDLE *handle = pHandle;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		return errno;		
	}
	handle->sockfd = sockfd;
	struct sockaddr_in addr; 
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port); 
	addr.sin_addr.s_addr = inet_addr(ip);

	int ret = connect_timeout(sockfd, (struct sockaddr *)&addr, (unsigned int)handle->conntime);
	if (ret < 0) {
		if (-1 == ret && errno == ETIMEDOUT) {
			return SOCKET_ERROR_TIMEOUT;
		}
		else {
			return errno;
		}
	}
	*confd = sockfd;
	return 0;
}

int sckClient_closeconn(int *connfd)
{
	close(*connfd);
	return 0;
}

/*
 * write check timeout, not write operator
 *
 * */
static int write_timeout(int pFd, int pWait_Seconds)
{
	int ret = 0;	
	if (pWait_Seconds > 0) {
		fd_set writefd;
		struct timeval timeout;
		FD_ZERO(&writefd);
		FD_SET(pFd, &writefd);
		timeout.tv_sec = pWait_Seconds;
		timeout.tv_usec = 0;
		do {
			ret = select(pFd + 1, NULL, &writefd, NULL, &timeout);
		} while (0 > ret && errno == EINTR) ;
		//ret has three status:
		//1.ret equal 0, indicate timeout.
		//2.ret equal 1, indicate writefd changed.
		//3.ret eqaul -1, indicate there was error occured.
		if (0 == ret) { 
			ret = -1;
			errno = ETIMEDOUT;
		}
		else if (1 == ret){
			ret = 0;
		}
		else {
			ret = errno;
		}
	}
	return ret;
}

int sckClient_send(void *pHandle, int connfd, unsigned char *data, int datalen)
{
	int ret = 0;
	SOCKET_HANDLE *handle = (SOCKET_HANDLE *)pHandle;
	ret = write_timeout(connfd, handle->sendtime);
	if (ret < 0) {
		if (-1 == ret && errno == ETIMEDOUT) {
			ret = SOCKET_ERROR_TIMEOUT;
		}
		return ret;
	}
	else if (0 == ret) { //ready to write.
		int writelen = 0;	
		unsigned char *writedata = (unsigned char *)malloc(sizeof(datalen + 4));
		if (NULL == writedata) {
			ret = SOCKET_ERROR_MALLOC;
			return ret;
		}
//		int netlen = htonl(datalen + 4);
//		memcpy(writedata, &netlen, 4);
//	    memcpy(writedata + 4, data, datalen);
		memcpy(writedata, data, datalen);
		writelen = write(connfd, writedata, datalen);
		if (writelen != datalen) {
			ret = errno;
		}
//		writelen = write(connfd, writedata, datalen + 4);
//		if (writelen < datalen + 4) {
//			
//		}
		free(writedata);
		writedata = NULL;
		//return writelen;
	}
	return 0;
}

/*
 * set read timeout
 * */
static int read_timeout(int pFd, int pRead_Timeout)
{
	int ret = 0;	
	if (pRead_Timeout > 0) {
		fd_set read_fdset;
		struct timeval timeout;
		FD_ZERO(&read_fdset);
		FD_SET(pFd, &read_fdset);
		timeout.tv_sec = pRead_Timeout;
		timeout.tv_usec = 0;
		do {
			ret = select(pFd + 1, &read_fdset, NULL, NULL, &timeout);
		} while (ret < 0 && errno == EINTR);
		//ret has three status:
		//1.ret equal 0, indicate timeout.
		//2.ret equal 1, indicate writefd changed.
		//3.ret eqaul -1, indicate there was error occured.
		if (0 == ret) {
			ret = -1;			
			errno = ETIMEDOUT;
		}
		else if (1 == ret) {
			ret = 0;	
		}
		else {
			ret = errno;
		}
	}
	return ret;
}

int sckClient_recv(void *pHandle, int connfd, unsigned char *outdata, int datalen)
{
	SOCKET_HANDLE *handle = (SOCKET_HANDLE *)(pHandle);
	int ret = read_timeout(connfd, handle->recvtime);
	if (ret < 0) {
		if (-1 == ret && ETIMEDOUT == errno) {
			ret = SOCKET_ERROR_TIMEOUT;	
		}
	}
	else if (0 == ret) {
		int readlen = 0;
		readlen = read(connfd, outdata, datalen);
	}
	return ret;
}

int sckClient_destory(void **pHandle)
{
	free(*pHandle);
	*pHandle = NULL;
	return 0;
}

