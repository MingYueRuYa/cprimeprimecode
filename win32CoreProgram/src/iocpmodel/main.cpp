/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

// #include "iocpserver.h"
// #include "tcpserver.h"
#include "app.h"

#include <iostream>

using std::cout;
using std::endl;

#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    // TcpServer().run("0.0.0.0", 9876);
    App().Run("0.0.0.0", 9876);

    getchar();

    return 0;
}


//int main01(int argc, char **argv)
//{
//	IOCPServer server;
//	server.LoadSocketLib();
//	server.Start();
//
////	CIOCPModel model;
////	model.LoadSocketLib();
////	model.Start();
//
//	while (1) {
//		Sleep(1000);
//	}
//
//	return 0;
//}