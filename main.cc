#include "ipc/IpcMaster.hh"
#include "my_asio/MyAsio.hh"


int main()
{
//    ipc::IpcMaster ipc;
//    ipc.run();

//    boost::asio::io_context io;

    my_asio::MyAsio ma;
    ma.run();

    return 0;
}

