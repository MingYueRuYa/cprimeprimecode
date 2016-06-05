#ifndef sockutil_h
#define sockutil_h

#include <stdio.h>
#include <unistd.h>

#ifdef _cplusplus
extern 'C'
{
#endif

//define error code
#define SOCKET_OK 0
#define SOCKET_BASE_ERROR 3000
#define SOCKET_ERROR_PARAMETER (SOCKET_BASE_ERROR + 1)
#define SOCKET_ERROR_TIMEOUT (SOCKET_BASE_ERROR + 2)
#define SOCKET_ERROR_PEER_CLOSED (SOCKET_BASE_ERROR + 3)
#define SOCKET_ERROR_MALLOC (SOCKET_BASE_ERROR + 4)

int sckClient_init(void **pHandle, int connecttime, int sendtime, int recvtime, int nConNum);

int sckClient_getconn(void *pHandle, char *ip, unsigned int port, int *confd);

int sckClient_closeconn(int *connfd);

int sckClient_send(void *pHandle, int connfd, unsigned char *data, int datalen);

int sckClient_recv(void *pHandle, int connfd, unsigned char *outdata, int datalen);

int sckClient_destory(void **pHandle);


//server encapsulation 
int sckServer_init(int port, int *listenfd);

int sckServer_accept(int listenfd, int *connfd, int timeout);

int sckServer_send(int connfd, char *data, int datalen, int timeout);

int sckServer_rec(int connfd, char *data, int *outlen, int timeout);

int sckServer_destory(void *handle);

#ifdef _cplusplus
}
#endif

#endif //sockutil_h

