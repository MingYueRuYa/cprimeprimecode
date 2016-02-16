#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int len = 0;
	char buf[1024] = {0};
	while (1) {
		len = read(STDIN_FILENO, buf, sizeof(buf));	
		if (len <= -1) {
			perror("Read stdin file error.\n");
		}
		write(STDOUT_FILENO, buf, len);
		if (len <= -1) {
			perror("Write stdin file error.\n");
		}
	}
	return 0;
}
