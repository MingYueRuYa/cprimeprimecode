/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <QtCore/QDebug>

#include "udp_client.h"

const int G_PORT = 6000;

UdpClient::UdpClient()
{
    mPort = G_PORT;
    mSocket = new QUdpSocket(this);
}

UdpClient::~UdpClient()
{
    if (NULL != mSocket) {
        delete mSocket;
        mSocket = NULL;
    }
}

bool UdpClient::Initialize()
{
	if (NULL == mSocket) {
		mSocket = new QUdpSocket(this);
	}
	if (! mSocket->bind(mPort)) {
		qDebug() << "socket bind port " + QString::number(mPort) + "failed.";
		return false;
	}
	connect(mSocket, SIGNAL(readyRead()), this, SLOT(DoSocketDataRecevied()));
	return true;
}

bool UdpClient::Finalize()
{
	return false;
}

void UdpClient::DoSocketClosed()
{
	if (NULL != mSocket) {
		delete mSocket;
		mSocket = NULL;
	}
}

void UdpClient::DoSocketDataRecevied()
{
	while (mSocket->hasPendingDatagrams()) {
		QByteArray msgarray;
		msgarray.resize(mSocket->pendingDatagramSize());
		int retlen = mSocket->readDatagram(msgarray.data(), msgarray.size());
		if (retlen < 0) {
			//error and reason
			qDebug() << "socket read error.";
		}
		else if (retlen >= 0) {
			qDebug() << "receive message:" << QString(msgarray);
		}
	}
}
