/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

#include "udp_client.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
    UdpClient client;
    if (! client.Initialize()) {
		qDebug() << "udpclient initialize error.";
	}
	return app.exec();
}
