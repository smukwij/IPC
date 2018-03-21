#pragma once

#include <string>

namespace ipc {
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
        int _socket_fd;
};





}
}
