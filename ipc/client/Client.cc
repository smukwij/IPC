#include "Client.hh"

#include <logging/Logging.hh>

#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "../connection/Connection.hh"

namespace ipc {
namespace client {

Client::Client()
    : _socket()
{
}
 
Client::~Client()
{
    logging::log_info << "~Client" << logging::end;
}

void Client::init(const std::string& addr)
{
    _socket.create();
    _socket.bind(addr);
}

void Client::connect( const std::string& server)
{
    _connection = connection::create<connection::Socket>(_socket, server); 
}

void Client::send_message(const std::string& message)
{
    _connection->send(message);
    _socket.receive();
}

void Client::shut_down(const std::string& addr)
{

}


}
}
