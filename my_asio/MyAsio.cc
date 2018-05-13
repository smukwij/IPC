#include "MyAsio.hh"

#include <logging/Logging.hh>

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

namespace my_asio
{


namespace 
{

    class Printer
    {
        public:
            Printer(boost::asio::io_context& io) 
                : _strand(io)
                , _t1(io, boost::asio::chrono::seconds(1))
                , _t2(io, boost::asio::chrono::seconds(1))
                , _counter(0)
            {
                _t1.async_wait(boost::asio::bind_executor( _strand, boost::bind(&Printer::print1, this)));
                _t2.async_wait(boost::asio::bind_executor( _strand, boost::bind(&Printer::print2, this)));
            }

            ~Printer()
            {
                logging::log_info << "Final value: " << _counter << logging::end;
            }

            void print1()
            {
                logging::log_info << "T1 Asynch call" << logging::end;
                if( 10 > _counter)
                {
                    logging::log_info << "T1 Counter: " << _counter << logging::end;
                    ++_counter;
                    _t1.expires_at(_t1.expiry() + boost::asio::chrono::seconds(1));
                    _t1.async_wait(boost::asio::bind_executor(_strand, boost::bind(&Printer::print1, this)));
                }
            }

            void print2()
            {
                logging::log_info << "T2 Asynch call" << logging::end;
                if( 10 > _counter)
                {
                    logging::log_info << "T2 Counter: " << _counter << logging::end;
                    ++_counter;
                    _t2.expires_at(_t2.expiry() + boost::asio::chrono::seconds(1));
                    _t2.async_wait(boost::asio::bind_executor( _strand, boost::bind(&Printer::print2, this)));
                }
            }


        private:
        boost::asio::io_context::strand _strand;
        boost::asio::steady_timer _t1;
        boost::asio::steady_timer _t2;
        int _counter;
    };
}


void MyAsio::run()
{
    boost::asio::io_context io;
    logging::log_info << "Start" << logging::end;

    Printer p1{io};
    boost::thread t{boost::bind(&boost::asio::io_context::run, &io)};
    io.run();
    t.join();

    logging::log_info << "End" << logging::end;
}




}

