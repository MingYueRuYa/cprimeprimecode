/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include <unistd.h>
#include <signal.h>

#include "udp_server.h"

using std::cout;
using std::endl;

bool G_FOREVER_LOOP = true;

static void TermHandle(int pSignal, siginfo_t *pSiginfo, void *pUnused)
{
	G_FOREVER_LOOP = false;
}

static void IntHandle(int pSignal, siginfo_t *pSiginfo, void *pUnused)
{
	G_FOREVER_LOOP = false;
}

static int SetupSignalHandle()
{
	struct sigaction termaction;
	termaction.sa_sigaction = TermHandle;
	if (sigaction(SIGTERM, &termaction, 0) < 0) {
		return false;
	}
	termaction.sa_sigaction = IntHandle;
	if (sigaction(SIGINT, &termaction, 0) < 0) {
		return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	//background run
	daemon(0, 0);
	UdpServer server;
	if (! server.Initialize()) {
		cout << "server initialize error." << endl;
		return -1;
	}
	int count = 0;
	while (G_FOREVER_LOOP) {
		sleep(5);
		if (! server.SendDatagram()) {
			cout << "send datagram error." << endl;
			return -1;
		}
		cout << ++count << endl;
	}
	return 0;
}

