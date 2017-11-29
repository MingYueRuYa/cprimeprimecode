#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

#define ERR_EIXT(message)   \
    do {    \
        perror(message);    \
        exit(EXIT_FAILURE);  \
    } while(0) 

#define SOCK_PATH "/tmp/sock_file"

void echo_client(sockfd)
{
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    while (1) {
        if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) {
            break;
        }

       write(sockfd, sendbuf, strlen(sendbuf)); 

       read(sockfd, recvbuf, sizeof(recvbuf));

       fputs(recvbuf, stdout);

       memset(sendbuf, 0, strlen(sendbuf));
       memset(recvbuf, 0, strlen(recvbuf));
    }
    close(sockfd);
}

int main(int argc, char *argv[])
{

    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);

    int ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        ERR_EIXT("connect");        
    }

    echo_client(sockfd);


    return 0;
}
