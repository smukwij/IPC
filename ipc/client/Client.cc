#include "Client.hh"

#include "../logging/Logging.hh"

#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>


namespace ipc {
namespace client {

Client::Client()
    : _socket_fd(-1)
{
}
 
Client::~Client()
{
    logging::log_info << "~Client" << logging::end();
}

void Client::init(const std::string& addr)
{
    _socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(-1 == _socket_fd)
    {
        logging::log_err << "Cannot crete socket! Error: " << errno << logging::end();
    }

    sockaddr_un my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sun_family = AF_UNIX;
    strcpy(my_addr.sun_path, addr.c_str());

    unlink(addr.c_str());
    if(-1 == bind(_socket_fd, (struct sockaddr*)&my_addr, sizeof(sockaddr_un)))
    {
        logging::log_err << "Cannot bind socket! Error: " << errno << logging::end();
    }
}

void Client::connect( const std::string& server)
{
    sockaddr_un server_addr;
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, server.c_str());

    socklen_t len = sizeof(sockaddr_un);
    if( -1 == ::connect(_socket_fd, (struct sockaddr*) &server_addr, len))
    {
        logging::log_err << "Cannot connect to socker! Error: " << (errno == EALREADY ? "Already connected" : std::to_string(errno)) << logging::end();
    }
}

void Client::send_message(const std::string& message)
{
    logging::log_info << "Client: before send" << logging::end();
    if( -1 == send(_socket_fd, message.c_str(), message.size(), 0))
    {
        logging::log_err << "Cannot send message! Error: " << errno << logging::end();
    }
    else
    {
        logging::log_info << "Data sent!" << logging::end();
    }
    char buf[256];
    logging::log_info << "Client: before receive" << logging::end();
    if(-1 == recv(_socket_fd, buf, sizeof(buf), 0))
    {
        logging::log_err << "Client: cannor receive! Error: " << errno << logging::end();
    }
    logging::log_info << "Client: received: " << buf << logging::end();
}

void Client::shut_down()
{
    close(_socket_fd);
}


}
}
