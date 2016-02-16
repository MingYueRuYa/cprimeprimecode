#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * 复制文件，源文件和目标文件
 * */
int main(int argc, char *argv[])
{
	char buf[1024] = {0};
	if (argc < 3) {
		printf("Input source file and destination file.\n");
		return 1;
	}	
	int sourcefd = open(argv[1], O_RDONLY);
	if (-1 == sourcefd ) {
		printf("Read file error.\n");
		return -1;
	}

	int desfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (-1 == desfd) {
		printf("Read file error.\n");
		return -1;
	}
	int len = 0;
	while ((len = read(sourcefd, buf, sizeof(buf))) > 0) {
		write(desfd, buf, len);
	}
	close(sourcefd);
	close(desfd);
	printf("Copy file complete.");
	return 0;
}
