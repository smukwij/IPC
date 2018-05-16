#include "ipc/IpcMaster.hh"
#include "my_asio/MyAsio.hh"


int main()
{
    my_asio::MyAsio ma;
    ma.run();

    return 0;
}

