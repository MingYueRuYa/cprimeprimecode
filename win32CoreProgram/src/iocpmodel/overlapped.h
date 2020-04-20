#ifndef overlapped_h
#define overlapped_h

#include "connection.h"

#include <WinSock2.h>

#define ReadBufferSize 1024

struct Overlapped
{
    enum Type
    {
        Connect_Type,
        Accept_Type,
        Read_Type,
        Write_Type
    };

    WSAOVERLAPPED overlapped;

    Type type;
    WSABUF wsa_buff;
    SOCKET _accepted_socket;
    Connection *connection;

};

inline Overlapped *CreateOverlapped(Overlapped::Type type)
{
    Overlapped *overlapped = new Overlapped();
    memset(overlapped, 0, sizeof(Overlapped));
    overlapped->type = type;
    return overlapped;
}

#endif // overlapped_h