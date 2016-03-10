#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int num)
{
	printf("signal number is %d.\n", num);
}

int main(void)
{
	printf("sleep...\n");
	signal(SIGINT, handler);
	int n = 3;
	while ( n > 0) {
		n = sleep(n);
	}
	printf("wakeup...\n");
	return 0;
}
