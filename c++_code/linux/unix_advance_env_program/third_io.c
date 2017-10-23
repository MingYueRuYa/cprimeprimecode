/*
 * 第三章：关于File IO
 * 测试环境：Linux 4.4.0-31-generic #50~14.04.1-Ubuntu SMP Wed Jul 13 01:06:37 UTC 2016 i686 i686 i686 GNU/Linux
 * */
#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "apue.h"
#include "error.c"

void test_read_from_stdin()
{
	char buffer[1024] = {0};
	while (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0) {
		printf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
	}
}

/*
 * lseek对于pipo和fifo文件不能定位
 * 实际测试时，如果输入的文件是pipe，程序就会卡主的问题
 * */
void test_lseek()
{
	printf("test lessk...\n");
	if (-1 == lseek(STDIN_FILENO, 0, SEEK_CUR)) {
		printf("cannot seek.\n");
	} else {
		printf("seek ok.\n");
	}
}

void test_create_file_hole()
{
	char buf1[] = "abcdefjh";
	char buf2[] = "ABCDEFJH";

	int fd;	
	if ( (fd = creat("file.hole", FILE_MODE)) < 0 ) {
		err_sys("creat error");
	}
	
	if (write(fd, buf1, strlen(buf1)) != strlen(buf1)) {
		err_sys("write error");	
	}

	if (-1 == lseek(fd, 40, SEEK_SET)) {
		err_sys("lseek error");
	}

	if ( write(fd, buf2, strlen(buf2)) != strlen(buf2) ) {
		err_sys("write buf2 error");
	}
}

/*
 * 复制文件
 * */
void test_read_write()
{
	const int BUFFSIZE = 8192;

	char buf[BUFFSIZE];
	int readlen = 0;
	int copyfd = 0;
	if ( (copyfd = open("./tmp.file", O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0) {
		err_sys("create file");
	}
	while ( (readlen = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if ( readlen != write(copyfd, buf, readlen) ) {
			err_sys("write error");
		}
	}

	if (readlen < 0) {
		err_sys("read error");
	}	
}

int main(int argc, char *argv[])
{
	//test_read_from_stdin();

	//test_lseek();

	//test_create_file_hole();

	test_read_write();

	return 0;
}

