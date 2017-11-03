#include "apue.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <limits.h>
#include <dirent.h>

#include "error.c"
#include "pathalloc.c"

int  g_argc 	= 0;
char **g_argv 	= NULL;

// 递归目录
typedef int MyFunc(const char *, const struct stat *, int);
static MyFunc myfunc;
static int myftw(char *, MyFunc *);
static int dopath(MyFunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

/*
 * 测试文件类型
 * */
void test_file_type();

/*
 * 测试umask
 * */
void test_umask();

/*
 * 测试chmod
 * */
void test_chmod();

/*
 * 测试unlink
 * 经常用来创建临时文件
 * */
void test_unlink();

/*
 * 测试utime
 * 修改读取时间(atime)，修改时间(mtime)
 * */
void test_utime();

/*
 * 递归搜索目录
 * */
int test_recurse_dir();

int
main(int argc, char *argv[])
{
	g_argc = argc;
	g_argv = argv;
//	test_file_type();
//	test_umask();
//	test_chmod();
//	test_unlink();
	test_utime();
	return 0;
}

void 
test_file_type()
{
	int 		i = 0;
	char 		*ptr;
	struct stat buf;
	for (i=1; i<g_argc; ++i) {
		printf("%s:", g_argv[i]);
		if ( lstat(g_argv[i], &buf) < 0) {
			err_ret("lstat error");
			continue;
		}
		if (S_ISREG(buf.st_mode)) {
			ptr = "regular";
		} else if (S_ISDIR(buf.st_mode)) {
			ptr = "directory";
		} else if (S_ISCHR(buf.st_mode)) {
			ptr = "character special.";
		} else if (S_ISBLK(buf.st_mode)) {
			ptr = "block special.";
		} else if (S_ISFIFO(buf.st_mode)) {
			ptr = "fifo.";
		}
#ifdef S_ISLNK
	   	else if (S_ISLNK(buf.st_mode)) {
			ptr = "symbolic special.";
		}
#endif
#ifdef S_ISSOCK
	   	else if (S_ISSOCK(buf.st_mode)) {
			ptr = "socket.";
		}
#endif
		else {
			ptr = "** unkown mode **";
		} //if
		printf("%s.\n", ptr);
	} // for
}

void 
test_umask()
{
	//先设置权限为0
	umask(0);
	if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
					 S_IROTH | S_IWOTH) < 0) {
		err_sys("creat error for foo");
	}

	//再设置组的权限：r,w 设置其他权限:r, w
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	if (creat("boo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
					 S_IROTH | S_IWOTH) < 0) {
		err_sys("creat error for foo");
	}
	//result:
	//-rw------- 1
	//-rw-rw-rw- 1
}

void 
test_chmod()
{
	//foo boo文件事先已存在
	struct stat statbuf;
	/* turn on set-group-ID and turn off group-execute */
	if (stat("foo", &statbuf) < 0) {
		err_sys("stat error for foo");
	}	
	
	if ( chmod("foo", ((statbuf.st_mode & ~S_IXGRP) | S_ISGID)) < 0) {
		err_sys("stat error for foo");
	}

	/* set absolute mode to "rw-r--r--" */
	if ( (chmod("boo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0 ) {
		err_sys("stat error for boo");
	}
	//result:
	//-rwxrwSrw- foo
	//-rw-r--r-- boo
}

void 
test_unlink()
{
	//创建一个300M的文件 利用dd指令
	if (open("tmp.300M", O_RDWR) < 0) {
		err_sys("open error for tmp.300M");
	}

	if (unlink("tmp.300M") < 0) {
		err_sys("unlink error for tmp.300M");
	}
	printf("file unlinked.\n");
	//sleep 15s
	sleep(25);
	printf("done.\n");
	//一旦程序退出tmp.300M文件就被删除，即使是异常退出也会删除
}

void 
test_utime()
{
	int 			i = 1;	
	struct stat 	statbuf;
	struct utimbuf 	timebuf;
	for (i=1; i<g_argc; ++i) {
		if (stat(g_argv[i], &statbuf) < 0) {	//fetch current time
			err_ret("%s: stat error", g_argv[i]);
			continue;
		}
		if (open(g_argv[i], O_RDWR | O_TRUNC) < 0) {	//truncate
			err_ret("%s: open error", g_argv[i]);
			continue;
		}

		timebuf.actime  = statbuf.st_atime;
		timebuf.modtime = statbuf.st_mtime;
		if (utime(g_argv[i], &timebuf) < 0) {	//reset time
			err_ret("%s: utime error", g_argv[i]);
			continue;
		}
	}
}

int
test_recurse_dir()
{
	int ret;
	if (g_argc != 2) {
		err_quit("usage: ftw <starting-pathname>");
	}
	//does it all
	ret = myftw(g_argv[1], myfunc);

	if ( (ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock) == 0) {
		//avoid divide by 0; print 0 for all counts
		ntot = 1;	
	}

	printf("regular files  = %7ld, %5.2f %%\n", nreg,   nreg*100.0/ntot);	
	printf("directories    = %7ld, %5.2f %%\n", ndir,   ndir*100.0/ntot);	
	printf("block special  = %7ld, %5.2f %%\n", nblk,   nblk*100.0/ntot);	
	printf("char special   = %7ld, %5.2f %%\n", nchr,   nchr*100.0/ntot);	
	printf("FIFIO 		   = %7ld, %5.2f %%\n", nfifo,  nfifo*100.0/ntot);	
	printf("symbolic links = %7ld, %5.2f %%\n", nslink, nreg*100.0/ntot);	
	printf("sockets		   = %7ld, %5.2f %%\n", nsock,  nsock*100.0/ntot);	
	exit(ret);
}

/*
 *	Descend through the hierarchy, starting at "pathname".
 *	The caller's func() is called for every file.
 * */

#define FTW_F	1	//file other than directory
#define FTW_D	2	//directory
#define FTW_NDR 3	//directory that can't be read
#define FTW_NS	4	//file that we can't stat

static char 	*fullpath;	//contains full pathname for every file
static size_t 	pathlen;

static int
myftw(char *pathname, MyFunc *func)
{
	fullpath = path_alloc(NULL);	//malloc's for PATH_MAX+1 bytes
	strcpy(fullpath, pathname);
	return (dopath(func));
}

/*
 * Descent through the hierarchy, starting at "fullpath".
 * if "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return, For a directory, we call ourself
 * recursively for each name in the directory
 * */
static int	//we return whatever func() returns
dopath(MyFunc *func)
{
	struct stat		statbuf;
	struct dirent	*dirp;
	DIR				*dp;
	int 			ret, n;
	
	if (lstat(fullpath, &statbuf) < 0) {	//stat error
		return (func(fullpath, &statbuf, FTW_NS));
	}

	if (S_ISDIR(statbuf.st_mode) == 0) {	//not a directory
		return (func(fullpath, &statbuf, FTW_F));
	}

	/*
	 * It's a directory. First call func() for the directory
	 * then process each filename in the directory
	 * */
	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) {
		return (ret);
	}

	n = strlen(fullpath);
	if (n + NAME_MAX + 2 > pathlen) {	//expand path buffer
		pathlen *= 2;
		if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
			err_sys("realloc failed.");
		} //if
	} //if
	
	fullpath[n++] = '/';
	fullpath[n]	  = 0;

	if ((dp = opendir(fullpath)) == NULL) {	//can't read directory
		return (func(fullpath, &statbuf, FTW_NDR));
	}

	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") == 0 ||
			strcmp(dirp->d_name, "..") == 0) {
			continue;	//ignore dot and dot-dot
		}
		strcpy(&fullpath[n], dirp->d_name);	//append name after
		if ((ret = dopath(func)) != 0) {	//recursive
			break;	//time to leave
		}
	} //while
	
	fullpath[n-1] = 0;	//erase everything from slash onward.

	if (closedir(dp) < 0) {
		err_ret("can't close directory %s.", fullpath);
	}
	return (ret);
}

static int
myfunc(const char *pathname, const struct stat *statptr, int type)
{
	switch(type)
	{
		case FTW_F:
			switch(statptr->st_mode & S_IFMT) {
				case S_IFREG: nreg++; break;
				case S_IFBLK: nblk++; break;
				case S_IFCHR: nchr++; break;
				case S_IFIFO: nfifo++; break;
				case S_IFLNK: nslink++; break;
				case S_IFSOCK: nsock++; break;
				case S_IFDIR:	//directoies should have type = FTW_D
						   err_dump("for S_IFDIR for %s", pathname);
			}
		case FTW_D:
			ndir++;
			break;
		case FTW_NDR:
			err_ret("can't read directory %s.", pathname);
			break;
		case FTW_NS:
			err_ret("stat error for %s.", pathname);
			break;
		deault:
			err_dump("unknow type %d for pathname %s", type, pathname);
	}
	return 0;
}









