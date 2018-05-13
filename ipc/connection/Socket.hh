#pragma once

#include <string>

namespace ipc {
namespace connection {


class Socket 
{
    public:
        using HandlerType = int;
        using AddrType = std::string;
        using PayloadType = std::string;

        Socket();
        ~Socket();

        int create();
        int bind( const AddrType& addr);
        int connect(const AddrType& server) const;

        int send(const PayloadType& message);
        PayloadType receive();

    private:
        HandlerType _handler;
        AddrType _addr;
};

}
}
