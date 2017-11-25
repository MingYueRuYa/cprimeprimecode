#include "sysutil.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "common.h"

static void activate_nonblock(int fd)
{
    int ret     = -1;
    int flags   =  fcntl(fd, GET_FL);
    if (-1 == flags) {
        ERR_EXIT("fcntl");
    }

    flags |= O_NONBLOCK;
    ret = fcntl(fd, SET_FL, flags);
    if (-1 == flags) {
        ERR_EXIT("fcntl");
    }
}

static void deactivate_nonblock(int fd)
{
    int ret     = -1;
    int flags   = fcntl(fd, GET_FL);
    if (-1 == flags) {
        ERR_EXIT("fcntl");
    }

    flags |= ~O_NONBLOCK;
    ret = fcntl(fd, SET_FL, flags);
    if (-1 == flags) {
        ERR_EXIT("fcntl");
    }
}

/*
 * read timeout 
 * @fd: 文件描述符
 * @wait_seconds: 等待超时时间
 * 成功（未超时，返回0，失败返回-1，超时返回-1 && errno = ETIMEOUT）
 * */
int read_timeout(int fd, unsigned int wait_seconds)
{
    int ret = -1;
    if (wait_seconds > 0) {
        fd_set read_fdset;
        FD_ZERO(&read_fdset);
        FD_SET(fd, &read_fdset);

        struct timeval timeout;
        timeout.tv_sec  = wait_seconds;
        timeout.tv_vsec = 0;

       do {
            ret = select(fd+1, &read_fdset, NULL, NULL, &timeout);
       } while (ret == -1 && errno = EINTR)
        
       if (0 == ret ) {  //被信号中断
           ret = -1; 
           errno = ETIMEOUT;
       } else if (1 == ret) {
           ret = 0; 
       }
    } // if

    return ret;
}

/*
 * write timeout 
 * @fd: 文件描述符
 * @wait_seconds: 等待超时时间
 * 成功（未超时，返回0，失败返回-1，超时返回-1 && errno = ETIMEOUT）
 * */
int write_timeout(int fd, , unsigned int wait_seconds)
{
    int ret = -1;
    if (wait_seconds > 0) {
        fd_set write_fdset;
        FD_ZERO(&write_fdset);
        FD_SET(fd, &write_fdset);

        struct timeval timeout;
        timeout.tv_sec  = wait_seconds;
        timeout.tv_vsec = 0;

       do {
            ret = select(fd+1, NULL, &write_fdset, NULL, &timeout);
       } while (ret == -1 && errno = EINTR)
        
       if (0 == ret ) {  //被信号中断
           ret = -1; 
           errno = ETIMEOUT;
       } else if (1 == ret) {
           ret = 0; 
       }
    } // if

    return ret;
}

/*
 * accpet timeout 
 * @fd: 文件描述符
 * @addr: 链接方的地址
 * @wait_seconds: 等待超时时间
 * 成功（未超时，返回0，失败返回-1，超时返回-1 && errno = ETIMEOUT）
 * */
int accept_timeout(int fd
                    , struct sockaddr_in *addr
                    , unsigned int wait_seconds)
{
    int ret = -1;

    if (wait_seconds > 0) {
        fd_set accept_fdset;
        FD_ZERO(&accpet_fdset);
        FD_SET(fd, &accept_fdset);

        struct timeval timeout;
        timeout.tv_sec  = wait_seconds;
        timeout.tv_vsec = 0;
        do {
            ret = select(fd+1, &accept_fdset, NULL, &timeout);
        } while (ret == -1 && errno == EINTR);
        
        if (-1 == ret) {
            return ret;
        } else if (0 == ret) {
            ret = -1;
            errno = ETIMEOUT;
            return ret;
        }
    }  

    socklen_t socklen = sizeof(struct sockaddr_in);
    if (NULL == addr) {
        ret = accept(fd, NULL, NULL);
    } else {
        ret = accept(fd, addr, &socklen);
    }

    return ret;
}

/*
 * connect timeout 
 * @fd: 文件描述符
 * @addr: 自己的IP地址
 * @wait_seconds: 等待超时时间
 * 成功（未超时，返回0，失败返回-1，超时返回-1 && errno = ETIMEOUT）
 * */
int connect_timeout(int fd
                    , struct sockaddr_in *addr
                    , unsigned int wait_seconds)
{
    int ret = -1;
    
    if (wait_seconds > 0) {
        activate_nonblock(fd);
    }

    socklen_t socklen = sizeof(struct sockaddr_in);
    ret = connect(fd, addr, &socklen); 
    if (-1 == ret && EINPROCESS == errno) {     // 正在处理过程中
        fd_set connect_fdset;
        FD_ZERO(&connect_fdset);
        FD_SET(fd, &connect_fdset);

        struct timeval timeout;
        timeout.tv_sec  = wait_seconds; 
        timeout.tv_vsec = 0;
        do {
            ret = select(fd+1, NULL, &connect_fdset, NULL, &timeout);
        } while (-1 == ret && EINTR == errno);

        if (0 == ret) {
            ret     = -1;
            errno   = ETIMEOUT;
        } else if (1 == ret) {
            // 返回1，可能有两种情况，一种建立间接成功，一种是套接字发生错误
            // 此时错误信息不是保存至errno变量中，因为需要调用getsockopt来获
            // 取
            int err = -1;
            socklen_t socklen = sizeof(err);
            ret = getsockopt(fd
                             , SOL_SOCKET   , SO_ERROR
                             , &err         , &socklen);
            if (-1 == sockoptret) { //函数调用失败，直接返回
                return -1;
            } else if (0 == sockoptret) {
                ret = 0;
            } else {
                errno = err;
                ret = -1;
            } // if
        } // if
    } // if

    
    // 恢复原来的描述符模式
    if (wait_seconds > 0) {
        deactivate_nonblock(fd);
    }
    return ret;
}

