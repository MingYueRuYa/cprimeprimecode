#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[])
{
	printf("hello program pid is %d.\n", getpid());
	int i = 0;
	for (; NULL != environ[i]; ++i) {
		printf("%s\n", environ[i]);
	}
	return 0;
}
