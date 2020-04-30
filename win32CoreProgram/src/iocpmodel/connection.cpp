#include "connection.h"
#include "overlapped.h"

int Connection::sID = 0;

class Connection::Impl
{
public:
    Impl(const SOCKET &socket, Connection *owner);
    ~Impl();

public:
    SOCKET _socket;

    char _read_buffer[ReadBufferSize];
    char _msg_buffer[ReadBufferSize*4]; // ÏûÏ¢»º³åÇø
    int _pos;

    std::size_t _write_buffer_size;

    std::unique_ptr<char> _write_buffer;

    std::size_t _sent_bytes;

    std::size_t _total_bytes;

    std::unique_ptr<Overlapped> _connect_overlapped;
    std::unique_ptr<Overlapped> _accept_overlapped;
    std::unique_ptr<Overlapped> _read_overlapped;
    std::unique_ptr<Overlapped> _write_overlapped;

    void Clear();
};

Connection::Impl::Impl(const SOCKET &socket, Connection *owner)
    : _socket(socket)
    , _connect_overlapped(CreateOverlapped(Overlapped::Connect_Type))
    , _accept_overlapped(CreateOverlapped(Overlapped::Accept_Type))
    , _read_overlapped(CreateOverlapped(Overlapped::Read_Type))
    , _write_overlapped(CreateOverlapped(Overlapped::Write_Type))
    , _sent_bytes(0)
    , _total_bytes(0)
    , _write_buffer(nullptr)
    , _write_buffer_size(0)
    , _pos(0)
{
    _connect_overlapped->connection = owner;
    _accept_overlapped->connection = owner;
    _read_overlapped->connection = owner;
    _write_overlapped->connection = owner;
}


Connection::Impl::~Impl()
{
    if (_socket) { closesocket(_socket); }
}

void Connection::Impl::Clear()
{
    _pos = 0;
    _sent_bytes = 0;
    _total_bytes = 0;
    _write_buffer_size = 0;
}

Connection::Connection(const SOCKET &socket)
    : _impl(new Impl(socket, this))
{
    this->mID = sID++;
}

Connection::~Connection()
{}

Overlapped* Connection::GetWriteOverlapped() const
{
    return _impl->_write_overlapped.get();
}

Overlapped* Connection::GetReadOverlapped() const
{
    return _impl->_read_overlapped.get();
}

Overlapped* Connection::GetAcceptOverlapped() const
{
    return _impl->_accept_overlapped.get();
}

Overlapped* Connection::GetConnectOverlapped() const
{
    return _impl->_connect_overlapped.get();
}

void Connection::SetTotalBytes(std::size_t value)
{
	_impl->_total_bytes = value;
}

std::size_t Connection::GetTotalBytes() const
{
	return _impl->_total_bytes;
}

void Connection::SetSentBytes(std::size_t value)
{
	_impl->_sent_bytes = value;
}

std::size_t Connection::GetSentBytes() const
{
	return _impl->_sent_bytes;
}

std::size_t Connection::GetReadBufferSize()
{
	return ReadBufferSize;
}

void *Connection::GetReadBuffer()
{
    return &_impl->_read_buffer;
}

void *Connection::GetWriteBuffer()
{
    return _impl->_write_buffer.get();
}

std::size_t Connection::GetWriteBufferSize()
{
    return _impl->_write_buffer_size;
}

void Connection::ResizeWriteBuffer(std::size_t new_size)
{
    _impl->_write_buffer.reset(new char[new_size]);
    _impl->_write_buffer_size = new_size;
}

SOCKET& Connection::GetSocket()
{
	return _impl->_socket;
}

int Connection::GetID() const
{
    return mID;
}

char *Connection::GetMsgBuffer() const
{
    return _impl->_msg_buffer;
}

int Connection::GetMsgPos() const
{
    return _impl->_pos;
}

void Connection::SetMsgPos(int pos)
{
    _impl->_pos = pos;
}

void Connection::Clear()
{
    _impl->Clear();
}
