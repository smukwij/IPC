#include "IpcMaster.hh"

#include <iostream>
#include "process/Process.hh"

namespace ipc 
{

IpcMaster::IpcMaster()
{
    std::cout << "Hello IpcMaster" << std::endl;
}

IpcMaster::~IpcMaster()
{
}

void IpcMaster::run()
{
    auto entry_point = []() {std::cout << "test" << std::endl;};
    
    process::Process process = process::create(entry_point);
}

};
