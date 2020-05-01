/****************************************************************************
**
** Copyright (C) 2019 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef tcpclient_h
#define tcpclient_h

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <cstdio>

#include <thread>
#include <iostream>

#include "../iocpmodel/message.hpp"

using std::thread;
using std::cout;
using std::endl;

#pragma comment(lib, "ws2_32.lib")

const int kBUFFSIZE = 1024*10;

class TcpClient
{
public:
    TcpClient()
    {
        _socket = INVALID_SOCKET;
		_pos = 0;
		memset(_buff, 0, kBUFFSIZE);
		memset(_msgBuff, 0, kBUFFSIZE * 4);
        InitSock();
    }

    ~TcpClient()
    {
        Close();
    }

    void InitSock()
    {
        WSADATA wsaData;
        WORD version = MAKEWORD(2, 2);
        WSAStartup(version, &wsaData);

        if (INVALID_SOCKET != _socket) {
            Close(); 
        }

        _socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (INVALID_SOCKET == _socket) {
            cout << "创建socket 链接失败..." << endl; 
        } else {
            cout << "创建socket 链接成功..." << (int)_socket << endl; 
        }
    }

    int run(const char *ip, unsigned short port)
    {
        int ret = Connect(ip, port);

        while (1) {
            if (ret == -1) { break; }

            if (! EchoFunc()) { break; }
        }

        printf("服务器已断开\n");

        return ret;
    }

    bool EchoFunc()
	{
		bool bret = false;
		do{
			int ret = SendData();
			if (ret == SOCKET_ERROR)
				break;
			ret = RecvData();
			if (ret >= 0)
				bret = true;
			
		} while (0);
		return bret;
	}

    int Connect(const char *ip, short port)
    {
        if (_socket == INVALID_SOCKET) { InitSock(); }

        sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(sockaddr_in));
        inet_pton(AF_INET, ip, &server_addr.sin_addr);
        server_addr.sin_port = htons(port);
        server_addr.sin_family = AF_INET;

        if (::connect(_socket, (sockaddr *)&server_addr, sizeof(server_addr))) {
			printf("sock:%d connect error server ip:%s port(%d)\n", _socket, ip, port);
			return -1;
        } else {
            printf("连接服务器成功。。。\n");
            return 1;
        }

    }

    int SendData()
    {
        printf("输入:");
		scanf("%s",_buff);
		int ret = send(_socket, _buff, strlen(_buff), 0);
		if (ret == SOCKET_ERROR)
			closesocket(_socket);
		return ret;
    }

    int SendData(MessageHeader *msgHeader, int len)
    {
        int ret = send(_socket, (const char *)msgHeader, len, 0);
		if (ret == SOCKET_ERROR)
			closesocket(_socket);

		return ret;
    }

    int SendData(MessageHeader *msgHeader)
    {
        int ret = send(_socket, (const char *)msgHeader, msgHeader->length, 0);
		if (ret == SOCKET_ERROR)
			closesocket(_socket);
        

		return ret;
    }

    /*
    int RecvData()
    {
        int ret = -1;
		do
		{
			ret = recv(_socket, _buff, kBUFFSIZE, 0);
			if (ret <= 0)
			{
				closesocket(_socket);
				break;
			}
			_buff[ret] = '\0';
			printf("Server Echo:%s\n", _buff);
		} while (0);
		return ret;
    }
    */

    int RecvData()
    {
        int ret = -1;
        MessageHeader *msg_header = nullptr;
        do {
            ret = recv(_socket, _buff, kBUFFSIZE, 0);
            if (ret <= 0) {
                closesocket(_socket);
                break;
            }
            
            memcpy(_msgBuff + _pos, _buff, ret);
            _pos += ret;

            while (_pos >= sizeof(MessageHeader)) {
                msg_header = (MessageHeader *)_msgBuff;
                if (msg_header->length <= _pos) {
                    _pos = _pos - msg_header->length; 
                    ProcessMessage(msg_header);
                    memcpy(_msgBuff, _msgBuff + msg_header->length, _pos);
                } else {
                    break;
                }
            }

        } while(0);

        return 0;
    }


    void ProcessMessage(MessageHeader *msgHeader)
    {
        switch (msgHeader->type)
		{
		case T_Login_Result:
			fprintf(stderr, "T_Login_Result 数据长度:%d\n", msgHeader->length);
			break;
		case T_Logout_Result:
			fprintf(stderr, "T_Logout_Result 数据长度:%d\n", msgHeader->length);
			break;
		case T_ERROR:
			fprintf(stderr, "T_ERROR\n");
		default:
			fprintf(stderr, "未知消息\n");
			break;
		}


    }

    //关闭服务器
	void Close()
	{
		if (_socket != INVALID_SOCKET)
		{
			closesocket(_socket);
			WSACleanup();
		}
	}

private:
    SOCKET _socket;
    char _buff[kBUFFSIZE];
    char _msgBuff[kBUFFSIZE*4];
    int _pos;
};


#endif // tcpclient_h