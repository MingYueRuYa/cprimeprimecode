    
    内核共享：
    随内核持续：一直存在直到内核自举或显式删除（System V消息队列、
        共享内存、信号量）

程序：完成特定功能的一系列有序指令的集合
可执行文件
代码段+数据段

进程：程序的一次动态执行过程
代码段+数据段+堆栈端+PCB

进程            程序
动态的          数据端
短暂的          永久的
堆栈端+PCB

一个进程只能对应一个程序
一个程序可以对应多个进程

进程是分配资源的基本单位
线程是程序执行的最小单位

线程共享进程数据，但也拥有自己的数据
1.线程ID
2.一组寄存器
3.栈
4.errno
5.信号状态
6.优先级

共享的：
UID，GID，EGID，CWD
signal dispatch table
memory map
file descriptors

线程调度竞争范围
进程内
系统内

进程                    线程
pid_t                   pthread_t
fork                    pthread_create
waitpid                 pthread_join
exit                    pthread_exit        //自杀
在main中调用return      在线程入口函数中调用return

僵尸进程                僵尸线程
waitpid                 pthread_join
                        pthread_detach
                        
kill                    pthread_cancle      //他杀



