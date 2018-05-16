#include <logging/Logging.hh>

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>

int main()
{
    try
    {
        const std::string host {"127.0.0.1"};
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::resolver resolver(io_context);
    
        logging::log_info << "Client: server addr: " << host << logging::end;
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, "daytime");
    
        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        for(;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if(boost::asio::error::eof ==  error)
            {
                break;
            }
            else if(error)
            {
                throw boost::system::system_error(error);
            }
            logging::log_info << "Client: data received: " << len << logging::end;
            std::cout.write(buf.data(), len);
        }

    }
    catch(std::exception& e)
    {
        logging::log_err << e.what() << logging::end;
    }

    return 0;
}
