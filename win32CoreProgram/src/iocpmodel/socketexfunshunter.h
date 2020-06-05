#ifndef socketexfunshunter_h
#define socketexfunshunter_h

#include <Windows.h>
#include <WinSock2.h>
#include <MSWSock.h>

typedef BOOL (WINAPI *AcceptExPtr)(SOCKET, SOCKET, PVOID, DWORD, DWORD, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL (WINAPI *ConnectExPtr)(SOCKET, const struct sockaddr *, int, PVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef void (WINAPI *GetAcceptExSockaddrsPtr)(PVOID, DWORD, DWORD, DWORD, LPSOCKADDR *, LPINT, LPSOCKADDR *, LPINT);

class SocketExFnsHunter
{
public:    
    SocketExFnsHunter() { Hunt(); }
    AcceptExPtr AcceptEx;
    ConnectExPtr ConnectEx;
    GetAcceptExSockaddrsPtr GetAcceptExSockaddrs;

private:
    void Hunt()
    {
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (INVALID_SOCKET == sock) { return; }

        const GUID acceptex = WSAID_ACCEPTEX;
        AcceptEx = (AcceptExPtr)get_extension_function(sock, &acceptex);

        const GUID connectex = WSAID_CONNECTEX;
        ConnectEx = (ConnectExPtr)get_extension_function(sock, &connectex);

        const GUID getacceptexsockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
        GetAcceptExSockaddrs = (GetAcceptExSockaddrsPtr)get_extension_function(sock, &getacceptexsockaddrs);

        closesocket(sock);
    }

    void *get_extension_function(SOCKET sock, const GUID *which_fn)
    {
        void *ptr = NULL;
        DWORD bytes = 0;
        WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, (GUID *)which_fn, sizeof(*which_fn), &ptr, sizeof(ptr), &bytes, NULL, NULL);

        return ptr;
    }

};


#endif // socketexfunshunter_h