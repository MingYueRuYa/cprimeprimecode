/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

/*
 * In Ubuntu 14.04
 * 1.append "user.debug" in /etc/rsyslog.d/50-default.conf
 * 2.command /etc/init.d/rsyslog restart (if this no work, try reboot machine.)
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <syslog.h>

int main(int argc, char *argv[])
{
	openlog("testlog", LOG_CONS | LOG_PID, 0);
	syslog(LOG_USER | LOG_DEBUG, "syslog test message generated in program %s \n", argv[0]);
	closelog();
	return 0;
}
