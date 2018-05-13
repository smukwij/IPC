#pragma once

#include <memory>

namespace ipc {
namespace connection {

template<class Socket>
class Connection;

template<class Socket>
std::unique_ptr<Connection<Socket>> create(Socket& client, const typename Socket::AddrType& server);

template<class Socket>
class Connection
{
public:
    ~Connection() = default;

    int send(const typename Socket::PayloadType& payload)
    {
        return _socket.send(payload);
    }


private:
    friend std::unique_ptr<Connection<Socket>> create<>(Socket& client, const typename Socket::AddrType& server);

    Connection(Socket& socket)
        : _socket (socket)
    {
    }

    Socket& _socket;
};

template<class Socket>
std::unique_ptr<Connection<Socket>> create(Socket& client, const typename Socket::AddrType& server)
{
    client.connect(server);
    Connection<Socket>* con = new Connection<Socket>(client);
    return std::unique_ptr<Connection<Socket>>{con};
}


}
}
