/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef udp_client_h

#define udp_client_h

#include <QtCore/QObject>
#include <QtNetwork/QUdpSocket>

class UdpClient : public QObject
{
	Q_OBJECT

public:
    UdpClient();

    ~UdpClient();

	bool Initialize();

	bool Finalize();

protected slots:
	void DoSocketClosed();

	void DoSocketDataRecevied();

private:
	int mPort;
	
	QUdpSocket *mSocket;

};

#endif //udp_client_h
