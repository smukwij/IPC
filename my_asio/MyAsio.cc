#include "MyAsio.hh"

#include <iostream>
#include <boost/asio.hpp>

namespace my_asio
{

void MyAsio::run()
{
    boost::asio::io_context io;
    boost::asio::steady_timer t{io, boost::asio::chrono::seconds(5)};

}




}

