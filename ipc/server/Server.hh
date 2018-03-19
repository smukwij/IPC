#pragma once

#include <string>

namespace ipc {
namespace server {


//TODO: create policies for connection strategy: UNIX socket, internet socket, named PIPEs and so on..
class Server
{
    public:
        Server();
        ~Server();

        void init(const std::string& addr);

        void wait_for_accept();

        void wait_for_message();

        void shut_down();
    private:
        int _socket_fd;
        int _client_socket_fd;
};





}
}
