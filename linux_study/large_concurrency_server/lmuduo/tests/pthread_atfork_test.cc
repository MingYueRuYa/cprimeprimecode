#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void prepare(void)
{
	printf("pid = %d prepare...\n", static_cast<int>(getpid()));
}

void parent(void)
{
	printf("pid = %d parent...\n", static_cast<int>(getpid()));
}

void child(void)
{
	printf("pid = %d child...\n", static_cast<int>(getpid()));
}

int main(int argc, char *argv[])
{
	printf("pid = %d Entering main...\n", static_cast<int>(getpid()));

	pthread_atfork(prepare, parent,  child);
	fork();

	printf("pid = %d Exiting main...\n", static_cast<int>(getpid()));
	return 0;
	// result:
		// pid = 1947 Entering main...
		// pid = 1947 prepare...
		// pid = 1947 parent...
		// pid = 1947 Exiting main...
		// pid = 1947 Entering main...
		// pid = 1947 prepare...
		// pid = 1948 child...
		// pid = 1948 Exiting main...
}
