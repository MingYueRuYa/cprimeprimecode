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

int g_argc = 0;
char **g_argv = NULL;

//flags are file status flags to turn on
static void set_file_flag(int fd, int flags);

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
 * 实际测试时，如果输入的文件是管道，cannot seek
 * 如果是FIFO文件的测试会卡主
 * */
void test_lseek()
{
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

void test_get_file_flag()
{
	int accmode = 0, val = 0;
	if (g_argc < 2) {
		err_quit("usage: a.out <descriptor#>");
	}

	if ( (val = fcntl(atoi(g_argv[1]), F_GETFL, 0)) < 0 ) {
		err_sys("fcntl error for fd %d", atoi(g_argv[1]));
	}

	accmode = val & O_ACCMODE;
	if (accmode == O_RDONLY) {
		printf("read only");
	} else if (accmode == O_WRONLY) {
		printf("write only");
	} else if (accmode == O_WRONLY) {
       printf("write only");
	} else if (accmode == O_RDWR) {
       printf("read write");
	} else {
		err_dump("unknown access mode");
	}

	if (val & O_APPEND) {
       printf(", append");
	} 
   	if (val & O_NONBLOCK) {
       printf(", nonblock");
	}

#if !defined(_POSIX_SOURCE) && defined(O_SYNC)
	if (val & O_SYNC) {
		printf(", synchronous writes.");
	}
#endif

	putchar('\n');
}     

static void
set_file_flag(int fd, int flags, int isopen)
{
	int val = 0;
	if ( (val = fcntl(fd, F_GETFL, 0)) < 0 ) {
		err_sys("fcntl F_GETFL error.");
	}

	if (1 == isopen) {
		val |= flags;
	} else {
		val &= ~flags;
	}

	if (fcntl(fd, F_SETFL, val) < 0 ) {
		err_sys("fctnl F_SETFL error.");
	}
}

int main(int argc, char *argv[])
{
	g_argc = argc;
	g_argv = argv;

	//test_read_from_stdin();

	//test_lseek();

	//test_create_file_hole();

	//test_read_write();

	test_get_file_flag();

	return 0;
}

