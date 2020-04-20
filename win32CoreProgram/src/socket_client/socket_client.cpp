// socket_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tcpclient.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
    TcpClient().run("127.0.0.1", 9876);

    getchar();

    getchar();
	return 0;
}

