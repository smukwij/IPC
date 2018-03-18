#include "ipc/IpcMaster.hh"
#include <cstdlib>
#include <string>


int main()
{
    ipc::IpcMaster ipc;
    ipc.run();

    return 0;
}

