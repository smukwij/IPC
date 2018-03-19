#include "IpcMaster.hh"

#include <unistd.h>
#include "process/Process.hh"

#include "server/Server.hh"
#include "client/Client.hh"

#include "logging/Logging.hh"

void client_fun()
{
    ipc::client::Client c;
    c.init("ipc.client");
    c.connect("ipc.server");

    for(int i = 0; i < 10; ++i)
    {
        ipc::logging::log_info << " counter: " << i << ipc::logging::end();
        c.send_message("some message");
    }
    ipc::logging::log_info << "client just before end" << ipc::logging::end();
    c.shut_down();
    ipc::logging::log_info << "End of client fun" << ipc::logging::end();
}

namespace ipc 
{

IpcMaster::IpcMaster()
{
    logging::log_info << "Hello IpcMaster" << logging::end();
}

IpcMaster::~IpcMaster()
{
    logging::log_info << "~IpcMaster" << logging::end();
}

void IpcMaster::run()
{
    ipc::server::Server s;
    s.init("ipc.server");

    process::Process process = process::create(client_fun);

    s.wait_for_accept();
    for(int i = 0; i < 10; ++i)
    {
        logging::log_info << " counter: " << i << logging::end();
        s.wait_for_message();
    }
    logging::log_info << "server just before end" << logging::end();
    s.shut_down();
    logging::log_info << "server ends" << logging::end();

}

}
