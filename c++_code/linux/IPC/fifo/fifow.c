/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <memory.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (mkfifo("fifop", 0644) < 0) {
		perror("mkfifo error");
		exit(-1);
	}
	int readfd = 0;
	if ((readfd = open("fifop", O_WRONLY, 0644)) < 0) {
		perror("open file fifop");
		exit(-1);
	}
	char content[512] = {0};
	while (fgets(content, sizeof(content), stdin)) {
		if ('q' == content[0]) {
			printf("quit.\n");
			exit(0);
		}
		if (write(readfd, content, strlen(content)) < 0) {
			return -1;
		}
		printf("\tread %s", content);
		memset(content, 0, sizeof(content));
	}
	return 0;
}
