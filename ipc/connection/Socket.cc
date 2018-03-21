#include "Socket.hh"
#include "../logging/Logging.hh"

#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


namespace ipc {
namespace connection {


int Socket::create()
{
    int socket_fd = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if(-1 == socket_fd)
    {
        logging::log_err << "Cannot crete socket! Error: " << std::to_string(errno) << logging::end;
        return -1;
    }
    return socket_fd;
}

int Socket::bind(const AddrType& addr, HandlerType client_handler)
{
    sockaddr_un my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sun_family = AF_UNIX;
    strcpy(my_addr.sun_path, addrr.c_str());

    unlink(addr.c_str());
    if(-1 == ::bind(client_handler, (struct sockaddr*)&my_addr, sizeof(sockaddr_un)))
    {
        logging::log_err << "Cannot bind socket! Error: " << std::to_string(errno) << logging::end;
        return -1;
    }
    return 0;
}

int Socket::connect(const AddrType& server, HandlerType client_handler)
    sockaddr_un server_addr;
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, server.c_str());

    socklen_t len = sizeof(sockaddr_un);
    if( -1 == ::connect(client_handler, (struct sockaddr*) &server_addr, len))
    {
        logging::log_err << "Cannot connect to socker! Error: " <<  std::to_string(errno) << logging::end;
        reutrn -1;
    }
    logging::log_info << "Connected to server: " << server << logging::end;
    return 0;
}

}
}
