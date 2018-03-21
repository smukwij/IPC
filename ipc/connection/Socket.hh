#pragma once

#include <string>

namespace ipc {
namespace connection {


class Socket 
{
    public:
        using HandlerType = int;
        using AddrType = std::string;

        static int create();
        static int bind( const AddrType& addr, HandlerType client_handler);
        static int connect(const AddrType& server, HandlerType client_handler);
};

}
}
