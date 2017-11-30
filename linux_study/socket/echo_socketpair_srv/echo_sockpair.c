/*****************************************************************************
**
**  Copyrigth (C) 2017 liushixiongcpp@163.com
**  All rights reserved
**
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#define ERR_EXIT(message)   \
        do{ \
            perror(message);    \
            exit(EXIT_FAILURE); \
        } while(0)

int main(int argc, char *argv[])
{
    int sockfds[2];

    int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, sockfds);
    if (ret < 0) {
        ERR_EXIT("socketpair"); 
    }

    pid_t pid = fork();

    if (pid < 0) {
        ERR_EXIT("fork"); 
    } else if (pid > 0) {   //parent process ret
        close(sockfds[1]);
        int val = 0;
        while (1) {
            sleep(1);
            ++val;
            write(sockfds[0], &val, sizeof(val));
            printf("%d sending data %d\n", getpid(), val);

            read(sockfds[0], &val, sizeof(val));
            printf("%d read data %d\n", getpid(), val);
        }
    } else if (pid == 0) {  //child process ret
        close(sockfds[0]);
        int val = 0;
        while (1) {
            sleep(1);
            read(sockfds[1], &val, sizeof(val));
            printf("%d read data %d\n", getpid(), val);

            ++val;
            write(sockfds[1], &val, sizeof(val));
            printf("%d sending data %d\n", getpid(), val);
        }
    }
    return 0;
}
