#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * 默认情况下，最多可以创建1024个文件，但是可以修改内核参数进行修改
 * */
int main(int argv, char *argc[])
{
	char name[1024];
	int i = 0;
	int fd = 0;
	for (; i < 1024; ++i) {
		sprintf(name, "file%d.txt", i);
		fd = open(name, O_CREAT, 0777);
		if (-1 == fd) {
			printf("Create file error. %s\n", name);

			continue;
		}
	}
	return 0;
}
