#include "apue.h"

#include <errno.h>	//for definition of errno
#include <stdarg.h>	//ISO c variable arguments

static void err_doit(int , int, const char *, va_list);


/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 * */
void
err_sys(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 * */
void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag) {
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
	}
	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL); //flushes all stdio ouput streams
}


