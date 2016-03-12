#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

typedef struct _Teacher
{
	char *name;
	unsigned int age;
}Teacher;

Teacher teacher;

void PrintTeacher()
{
	printf("teacher name %s.\n", teacher.name);
	printf("teacher age %d.\n", teacher.age);
}

void hanlder(int signum)
{
	printf("Ths signal num is %d.\n", signum);
	PrintTeacher();
	alarm(1);
}

/*演示不可重入函数，表示内部维持了一个全局变量或者一个静态变量，一致每次调用的时候结果是不确定的*/
int main(void)
{
	Teacher t1;
	t1.name = "linxu";
	t1.age = 15;
	Teacher t2;
	t2.name = "unix";
	t2.age = 25;

	if (SIG_ERR == signal(SIGALRM, hanlder)) {
		printf("Install signal error.\n");	
		return -1;
	}
	alarm(1);
	while (1) {
		teacher = t1;
		teacher = t2;
	}
	return 0;

}
