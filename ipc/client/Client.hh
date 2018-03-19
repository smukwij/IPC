#pragma once

#include <string>

namespace ipc {
namespace client {


//TODO: create policies for connection strategy: UNIX socket, internet socket, named PIPEs and so on..
class Client
{
    public:
        Client();
        ~Client();

        void init(const std::string& addr);
        void connect(const std::string& server);
        void send_message(const std::string& message);

        void shut_down();
    private:
        int _socket_fd;
};





}
}
