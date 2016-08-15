/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>

#include <unistd.h>
#include <signal.h>

#include "udp_server_config.h"
#include "udp_server.h"

#ifdef OPEN_GLOG
	#include <glog/logging.h>
#endif 

const int G_TRY_COUNT = 50;
const int G_SLEPP_TIME = 5;

using std::cout;
using std::endl;

bool G_FOREVER_LOOP = true;

static void TermHandle(int pSignal, siginfo_t *pSiginfo, void *pUnused)
{
	G_FOREVER_LOOP = false;
#ifdef OPEN_GLOG
	LOG(INFO) << "receive signal num:" << pSignal;
	google::ShutdownGoogleLogging();
#endif
}

static void IntHandle(int pSignal, siginfo_t *pSiginfo, void *pUnused)
{
	G_FOREVER_LOOP = false;
#ifdef OPEN_GLOG
	LOG(INFO) << "receive signal num:" << pSignal;
	google::ShutdownGoogleLogging();
#endif
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
	SetupSignalHandle();
	
#ifdef OPEN_GLOG
	google::InitGoogleLogging(APPLICATION_NAME);
	FLAGS_logbufsecs = 0;
#endif 

	UdpServer server;
	//if initialize error, try more time
	int trycount = 0;
	while (true) {
		if (server.Initialize()) {
#ifdef OPEN_GLOG
			LOG(INFO) << "Initialize ok......";
#endif 
			break;
		}
		sleep(G_SLEPP_TIME);
		if (trycount > G_TRY_COUNT){
			return -1;
		}
		trycount++;
	}
	while (G_FOREVER_LOOP) {
		//if send datagram error, try more time.
		if (! server.SendDatagram()) {
#ifdef OPEN_GLOG
			LOG(ERROR) << "Send datagram error.";
#endif 
		}
		sleep(G_SLEPP_TIME);
	}

#ifdef OPEN_GLOG
	google::ShutdownGoogleLogging();
#endif 

	return 0;
}

