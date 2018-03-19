#include "Server.hh"

#include "../logging/Logging.hh"

#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

namespace ipc {
namespace server {


Server::Server()
    : _socket_fd(-1)
    , _client_socket_fd(-1)
{
}

Server::~Server()
{
    logging::log_info << "~Server" << logging::end();
}

void Server::init(const std::string& addr)
{
    _socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(-1 == _socket_fd)
    {
        logging::log_err << "Cannot crete socket! Error: " << errno << logging::end();
    }

    sockaddr_un my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, addr.c_str(), sizeof(my_addr.sun_path)-1);

    unlink(addr.c_str());
    if(-1 == bind(_socket_fd, (struct sockaddr*)&my_addr, sizeof(sockaddr_un)))
    {
        logging::log_err << "Cannot bind socket! Error: " << errno << logging::end();
    }

    constexpr int backlog = 20;
    if( -1 == listen(_socket_fd, backlog ))
    {
        logging::log_err << "Cannot listen socket! Error: " << errno << logging::end();
    }
}

void Server::wait_for_accept()
{
    sockaddr_un client_addr;
    uint32_t len = sizeof(sockaddr_un);
    _client_socket_fd = accept( _socket_fd, (struct sockaddr*)&client_addr, &len);

    if( -1 == _client_socket_fd )
    {
        logging::log_err << "Cannot accept! Error: " << errno << logging::end();
        close (_client_socket_fd);
        return;
    }

    logging::log_info << "Client addr: " << client_addr.sun_path << logging::end();
}


void Server::wait_for_message()
{
    char buf[256];
    logging::log_info << "Server before recv" << logging::end();
    if( -1 == recv(_client_socket_fd, buf, sizeof(buf), 0))
    {
        logging::log_err << "Cannot recv! Error: " << strerror(errno) << logging::end();
        close(_client_socket_fd);
        return;
    }
    logging::log_info << "Data received: " << buf << logging::end();

    std::string OK = "OK";
    logging::log_info << "Server before send" << logging::end();
    if( -1 == send(_client_socket_fd, OK.c_str(), OK.size(), 0))
    {
        logging::log_err << "Server:: cannot send respoonse! Error: " << errno << logging::end();
    }
    logging::log_info << "Server data sent" << logging::end();
}

void Server::shut_down()
{
    close( _client_socket_fd);
    close(_socket_fd);
}

}
}
