#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void handler(int signum)
{
	printf("signal num is %d.\n", signum);
}


int main(void)
{
	signal(SIGINT, handler);	
	signal(SIGQUIT, handler);	
	while (1) {
		pause();
	}
	
	return 0;
}
	
