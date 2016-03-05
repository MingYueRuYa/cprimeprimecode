#include <unistd.h>
#include <stdio.h>

int main()
{
	fork();
	fork();
	fork();
	printf("hello\n");
	return 0;
}
