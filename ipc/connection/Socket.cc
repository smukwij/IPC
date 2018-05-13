#include "Socket.hh"
#include <logging/Logging.hh>

#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


namespace ipc {
namespace connection {

Socket::Socket() = default;

Socket::~Socket()
{
    logging::log_info << "Client close status: " <<strerror(close(_handler)) << logging::end;
    unlink(_addr.c_str());
}

int Socket::create()
{
    _handler = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if(-1 == _handler)
    {
        logging::log_err << "Cannot crete socket! Error: " << std::to_string(errno) << logging::end;
        return -1;
    }
    return _handler;
}

int Socket::bind(const AddrType& addr)
{
    sockaddr_un my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sun_family = AF_UNIX;
    strcpy(my_addr.sun_path, addr.c_str());

    unlink(addr.c_str());
    if(-1 == ::bind(_handler, (struct sockaddr*)&my_addr, sizeof(sockaddr_un)))
    {
        logging::log_err << "Cannot bind socket! Error: " << std::to_string(errno) << logging::end;
        return -1;
    }
    _addr = addr;
    return 0;
}

int Socket::connect(const AddrType& server) const
{
    sockaddr_un server_addr;
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, server.c_str());

    socklen_t len = sizeof(sockaddr_un);
    if( -1 == ::connect(_handler, (struct sockaddr*) &server_addr, len))
    {
        logging::log_err << "Cannot connect to socker! Error: " <<  std::to_string(errno) << logging::end;
        return -1;
    }
    logging::log_info << "Connected to server: " << server << logging::end;
    return 0;
}

int Socket::send(const PayloadType& message)
{
    if( -1 == ::send(_handler, message.c_str(), message.size(), 0))
    {
        logging::log_err << "Cannot send message! Error: " <<  std::to_string(errno) << logging::end;
        return -1;
    }
    logging::log_info << "Data: '" << message << "'  sent!" << logging::end;
    return 0;
}

Socket::PayloadType Socket::receive()
{
    char buf[256];
    if(-1 == recv(_handler, buf, sizeof(buf), 0))
    {
        logging::log_err << "Client: cannor receive! Error: " << std::to_string(errno) << logging::end;
        return std::string{};
    }
    logging::log_info << "Client: received: " << buf << logging::end;
    return std::string{buf};
}




}
}
