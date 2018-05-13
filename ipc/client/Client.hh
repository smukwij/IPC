#pragma once

#include <string>
#include <memory>
#include "../connection/Socket.hh"

namespace ipc {

namespace connection
{
class Socket;

template<class Socket>
class Connection;
}


namespace client {


class Client
{
    public:
        Client();
        ~Client();

        void init(const std::string& addr);
        void connect(const std::string& server);
        void send_message(const std::string& message);

        void shut_down(const std::string& addr);
    private:
        connection::Socket _socket;
        std::unique_ptr<connection::Connection<connection::Socket>> _connection;
};





}
}
