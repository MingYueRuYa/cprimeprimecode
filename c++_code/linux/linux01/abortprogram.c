/*
 * 终止程序的5中方法
 * 	1.从main函数返回
 * 	2.调用C库函数exit(0)
 * 	3.调用系统调用函数_exit();
 * 异常终止：
 * 	4.调用abort函数
 * 	5.信号终止Ctrl+c abort信号
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void Bye01(void)
{
	printf("Bye01......\n");
}


void Bye02(void)
{
	printf("Bye02......\n");
}

int main(void)
{
	printf("hello world");
	//注册程序退出时的回调函数，先注册后调用的机制，类似栈机制
	atexit(Bye01);
	atexit(Bye02);
	//fflush(stdout); //可以强制刷新缓冲区的内容
	//_exit(0); //系统调用函数，不会打印出hello world
	exit(0);// C库函数可以照常打印
	//abort(); //异常终止的时候不会调用程序的注册回调函数
	return 0;
}
