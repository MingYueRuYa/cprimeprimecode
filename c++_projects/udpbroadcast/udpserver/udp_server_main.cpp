/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <iostream>
#include <unistd.h>

#include "udp_server.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	UdpServer server;
	if (! server.Initialize()) {
		cout << "server initialize error." << endl;
		return -1;
	}
	int count = 0;
	while (1) {
		sleep(5);
		if (! server.SendDatagram()) {
			cout << "send datagram error." << endl;
			return -1;
		}
		cout << ++count << endl;
	}
	return 0;
}

