#include <iostream>
#include <ctime>
#include <boost/asio.hpp>
#include <string>

#include <logging/Logging.hh>


std::string make_daytime()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

int main()
{
    using namespace boost::asio::ip;
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor (io_context, tcp::endpoint(tcp::v4(),13));
        for(;;)
        {
            logging::log_info << "Server: waiting for connection" << logging::end;
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            logging::log_info << "Server: New conenction" << logging::end;

            std::string message = "My daytime: " + make_daytime() + " end";
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
            logging::log_info << "Server: data: " << message << " sent" << logging::end;
            logging::log_info << "Server: data size: " << message.size()  << logging::end;
        }
    }
    catch(std::exception& e)
    {
        logging::log_err << e.what() << logging::end;
    }

    return 0;
}
