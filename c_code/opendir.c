//获取目录大小

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	DIR *dir;
	if (NULL != (dir = opendir("/home/liushixiong/Downloads"))) {
		printf("dir size %d.\n", dir->_size);
	}
	closedir(dir);
	return 0;
}
