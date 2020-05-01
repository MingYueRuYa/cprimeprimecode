// socket_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "tcpclient.hpp"

/*
#define ClientCount 15000
#define Thread_Count 2

TcpClient *client[ClientCount];

void ClientSendThread(int id)
{
    Login login[100];

    for (int i = 0; i < 100; ++i) {
        strcpy(login[i].name, "xiaoming");
        strcpy(login[i].passwrod, "123456789");
    }

    int thread_clients_num = ClientCount / Thread_Count;
    int begin = (id-1)*thread_clients_num;
    int end = id * thread_clients_num;
    int len = sizeof(login);

    while (1) {
        for (int i = begin; i < end; ++i) {
            client[i]->SendData(login, len);
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    for (int i = 0; i < ClientCount; i++) {
        client[i] = new TcpClient();
        client[i]->Connect("127.0.0.1", 9876);
    }

    for (int i = 0; i < Thread_Count; ++i) {
        std::thread td(ClientSendThread, i+1);
        td.detach();
    }

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return;
}
*/

#define ClientCount 10
TcpClient *client[ClientCount];

int _tmain(int argc, _TCHAR* argv[])
{
// 单线程多个客户端连接服务器，给服务器发送数据

    Login login;
    strcpy(login.name, "xiaoming");
    strcpy(login.passwrod, "1234567890");

    for (int i = 0; i < ClientCount; ++i) {
        client[i] = new TcpClient();
        client[i]->Connect("127.0.0.1", 9876);
    }

    while (1) {
            client[0]->SendData(&login);
            client[0]->RecvData();
        /*
        for (int i = 0; i < ClientCount; ++i) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(5));
            client[i]->SendData(&login);
        }
        */
    }

	return 0;
}

