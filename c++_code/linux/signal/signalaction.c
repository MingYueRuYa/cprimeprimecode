#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


typedef struct _Teacher
{
	char *Name;
	unsigned int Age;
}Teacher;

void Handler(int signum, siginfo_t *info, void *p)
{
	printf("signum is %d.\n", signum);
	//printf("siginfo_t value %d.\n", info->si_int);
	//在第一次的时候是由sigqueue发送信号，info->si_value.sival_int是3，之后在发送SIGINT信号时，info->si_value.sival_int是0， 但是上面的刚开始时候也是3，但之后就是此进程的pid号
	printf("siginfo_t value %d.\n", info->si_value.sival_int);
}

//注意多进程的信号安装问题，可能造成段错误现象，注意
void Handler02(int signum, siginfo_t *info, void *p)
{
	//printf("address is %x.\n", info->si_value.sival_ptr);
	//return;
	if (NULL == info->si_value.sival_ptr) {
		return;
	}
	Teacher *teacher = (Teacher *)(info->si_value.sival_ptr);
	printf("pid is %d, teacher name %s, age %d.\n",info->si_pid, teacher->Name, teacher->Age);
}

int main(void)
{
	struct sigaction act;
	//act.sa_sigaction = Handler;	
	act.sa_sigaction = Handler02;	
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	union sigval v;
	//v.sival_int = 3;
	Teacher teacher;
	teacher.Name = "linux";
	teacher.Age = 12;
	v.sival_ptr = (void *)(&teacher);
	int ret = sigqueue(getpid(), SIGINT, v);
	
//	pid_t pid = fork();
//	if (-1 == pid) {
//		return -1;	
//	}
//	if (0 == pid) {
//		printf("child process pid is %d.\n", getpid());
//		int i = 0, ret = 0;
//		for (; i < 10; ++i) {
//			++teacher.Age;
//			ret = sigqueue(getpid(), SIGINT, v);
//			if (ret < 0) {
//				printf("sigqueue error.\n");
//			}
//		}
//		while (1) {
//			sleep(1);
//		}
//	}
//
	while (1) {
		sleep(1);
	}
	return 0;
}

int main_One_Process(void)
{
	struct sigaction act;
	//act.sa_sigaction = Handler;	
	act.sa_sigaction = Handler02;	
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	union sigval v;
	//v.sival_int = 3;
	Teacher teacher;
	teacher.Name = "linux";
	teacher.Age = 12;
	v.sival_ptr = (void *)(&teacher);
	sigqueue(getpid(), SIGINT, v);
	while (1) {
		sleep(1);
	}
	return 0;
}
