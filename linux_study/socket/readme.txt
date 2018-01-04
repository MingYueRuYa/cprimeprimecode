echosrv 使用read,write函数发送存在粘包问题
解决粘包的问题：
echo_n_srv 使用readn,writen自定义协议发送数据
echo_readline_srv 每次读取一行，以'\n'结束符


1.多进程框架
2.关闭不需要的fd
3.客户端退出
4.reuseaddr -> socket option


1.点对点聊天的程序，父子进程退出的问题

第四章：
1.流协议与粘包
2.粘包产生的原因
总的来说，就是缓冲区大小的限制
3.粘包处理方案
本质上是要在应用层维护消息的与消息的边界
	定包长
	包尾加\r\n (ftp)
	包头加上包体长度
	更复杂的应用层协议
4.readn writen
5.回射客户端/服务端

第五章：
1.read,write与recv,send
2.readline实现
3.用readline回射服务器/客户端
4.getsockname,getpeername
获得自己已经连接时，自己的地址和端口。获取已连接的socket对等方的地址和端口
5.gethostname,gethostbyname,gethostbyaddr

第六章：
TCP回射服务器/客户端
TCP是个流协议
僵尸进程与SIGCHLD信号
    1.忽略SIGCHLD信号
    2.处理SIGCHLD中调用wait函数

第七章：
    TCP 11种状态的转换
        状态的转换以及实验测试
    连接建立3次握手，连接终止4次握手
    TIME_WAIT与SO_REUSEADDR
    SIGPIPE产生：
        服务器段断开连接，客户段write时，tcp协议栈会返回FIN标志（表示不可读但是
        可以写数据）。然后客户端在write一次就收到RESET（tcp重置）标志，此时管道
        破裂就会收到SIGPIPE信号，一般情况下忽略此信号就行了 

第八章：
    五中I/O模型
        阻塞I/O
        非阻塞I/O
        I/O复用(select和poll)
        信号驱动I/O
        异步I/O
    select
    用select改进回射服务器

 第十二章
    select限制
        程序设置限制getrlimit setrlimit
        select 实现的并发服务器，能达到的并发数，收到来那个方面的限制
            1.一个进程能打开的最大文件描述符限制，这个可以通过调整内核参数
            2.select的fd_set集合容量的限制（FD_SETSIZE），这需要重新编译内核
            测试最大文件描述符限制
		
		可读事件：
			1.套接口缓冲区有数据可读
			2.连接的读一半关闭，既收到FIN段，读操作将返回0
			3.如果是监听套接口，已完成连接队列不为空时
			4.套接口上发生了一个错误待处理，错误可以通过getsockopt指定SO_ERROR
				选项来获取
		可写事件：
			1.套接口发送缓冲区有空间容纳数据
			2.连接的写一半关闭。既收到RST段之后，再次调用write操作
			3.套接口上发生了一个错误待处理，错误可以通过getsockopt指定SO_ERROR
				选项来获取

		异常事件：
			套接口存在带外数据

    poll

第十三章
	epoll使用
	epoll与select，poll区别
	epoll LT/ET模式
		epoll_create(int size) //size表示内部的一个hashtable大小
		epoll_create1(int flag) //对于较高的内核内部使用的是rb_tree实现的

	select
		1.一个进程的最大描述符个数有限制
		2.fd_set限制1024
	poll
		1.一个进程的最大描述符个数限制
	共同点：
		select,poll内核都要遍历所有文件描述符，
		直到找到发生时间的文件描述符
		
	可以查看/proc/sys/fs/file-max 一个系统最多可以打开多少的描述符，
        和内存相关 1G->100,000 10G->百万级别

        epoll与select，poll区别
        1.相比于select与poll，
            epoll最大的好处在于它不会随着监听fd数目的增加而降低效率
        内核中的select与poll的实现是采用轮询来处理的，
            轮询的fd数目越多，效率越低
        2.epoll的实现是基于回调的，如果fd有期望的事件发生就通过回调函数
            将其加入epoll的就绪队列中，也就是说他只关心活跃的放到
            ， 与fd数目多少没有关系
        3.内核/用户空间内存拷贝问题，如何让内核把fd消息通知给用户空间？
            在这个问题上select/poll采用了内存拷贝方式
            ，而epoll采用了共享内存的方式
        4.epoll不仅会告诉应用程序有I/O事件，
            因此根据这些信息应用程序就能直接定位到事件，而不必遍历整个fd集合


第十四章：
    UDP特点
        无连接
        基于消息的数据传输服务
        不可靠
        一般情况下UDP更加高效
    UDP客户端/服务器基本模型
    UDP回射客户端/服务器
    UDP注意点
        1.UDP可能会丢失，重复
        2.UDP报文可能会乱序
        3.缺乏流量控制
        4.UDP协议数据报文截断
        5.recvfrom返回0，不代表连接关闭，因为udp是无连接
        6.ICMP异步错误
            这个错误不会返回给未连接的socket套接口，所以recvfrom不会收到错误返
            回的信息，所以udp客户端也要调用connect就会收到一个ICMP信息
        7.UDP connect
        8.UDP外出接口的确定

第十五章：
	unix域协议特点
		unix域套接字域TCP套接字相比较，同一台主机前者是后者的2倍
		可以在同一台主机上各进程之间传递描述符
		unix域套接字与传统套接字的区别使用路径名来表示协议组的描述
	unix域地址结构
	unix域字节流回射客户/服务
	unix域套接字编程注意点
		bind成功将会创建一个文件，权限为0777 & ~mask
		sun_path最好用一个绝对路径，一般放在/tmp/目录下
		unix域协议支持流式套接口与报式套接口
		unix域流协议套接字connect发现监听队列满时，会立刻返回一个
		RECONNECTREFUSED，这个和TCP不同，如果监听队列满，会忽略到来的SYN
		，这导致对方重传SYN
		
第十六章：
socketpair
    功能：创建一个全双工的流管道，具有血缘关系的进程(父子进程)

    原型：
        int socketpair(int domain, int type, int protocal, int sv[2])
    参数：
        domain:协议家族
        type:套接字类型
        protocal:协议类型
        sv:返回套接字对
    返回值：
        成功返回0，失败返回-1
sendmsg/recvmsg
    ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
    ssize_t recvmsg(int sockfd, const struct msghdr *msg, int flags);
    writev
unix域协议传递描述符字
    父子进程之间可以传递，没有关系的进程也可以传递但是只能使用unix域协议
    不能使用socketpair进行
