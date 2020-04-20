#ifndef connection_h
#define connection_h

#include <WinSock2.h>
#include <memory>

struct Overlapped;

#define ReadBufferSize 1024

class Connection
{
public:
    Connection(const SOCKET &socket);
    ~Connection();

    SOCKET &GetSocket();

    void *GetReadBuffer();
    std::size_t GetReadBufferSize();

    void *GetWriteBuffer();
    std::size_t GetWriteBufferSize();

    void ResizeWriteBuffer(std::size_t new_size);

    std::size_t GetSentBytes() const;
    void SetSentBytes(std::size_t value);
    
    std::size_t GetTotalBytes() const;
    void SetTotalBytes(std::size_t value);

    Overlapped *GetConnectOverlapped() const;
    Overlapped *GetAcceptOverlapped() const;
    Overlapped *GetReadOverlapped() const;
    Overlapped *GetWriteOverlapped() const;

    int GetID() const;

private:
    class Impl;
    std::unique_ptr<Impl> _impl;
    int mID;

    static int sID;
};


#endif // connection_h
