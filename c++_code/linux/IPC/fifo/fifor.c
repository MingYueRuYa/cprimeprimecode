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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	//ready to write.
	int writefd = 0;
	if ((writefd = open("./test01.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0) {
		perror("open test01.txt error");
		return -1;
	}
	
	int readfd = 0;
	if ((readfd = open("fifop", O_RDONLY)) < 0) {
		perror("open fifop error");	
		return -1;
	}

	char content[512] = {0};
	int readlen = 0;
	while ((readlen = read(readfd, content, sizeof(content))) > 0) {
		if (write(writefd, content, strlen(content)) < 0) {
			perror("write to test01.txt error");
			return -1;
		}
	}

	close(writefd);
	close(readfd);
	//delete fifop and sub link number. if want delete file, you must have permission to dir.
	unlink("fifop");
	return 0;
}
