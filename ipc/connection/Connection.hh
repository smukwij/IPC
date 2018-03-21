#pragma once


namespace ipc {
namespace connection {

template<class Socket>
class Connection;

template<class Socket>
Connection<Socket> create(const typename Socket::AddrType& client, const typename Socket::AddrType& server)
{
    Connection<Socket> con{};
    con._client_addr = client;
    con._client_handler = Socket::create();
    Socket::bind(client, con._client_handler);
    Socket::connect(server, con._client_handler);
    return con;
}




template<class Socket>
class Connection
{
public:
    ~Connection() = default;

private:
    friend Connection<Socket> create<>(const typename Socket::AddrType& client, const typename Socket::AddrType& server);

    Connection() = default;

    typename Socket::HandlerType _client_handler;
    typename Socket::AddrType _client_addr;
};

}
}
