#include "Process.hh" 


#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

namespace ipc {
namespace process {

Process::Process() = default;

Process::~Process() = default;

Process create(std::function<void()> entry_point)
{
    std::cout << "Before fork: " << getpid() << std::endl;
    pid_t pid = fork();

    switch(pid){
    case 0:
        std::cout << "After fork: " << getpid() << std::endl;
        entry_point();
        break;
    default:
        int status = 0;
        std::cout << "pid: " << pid << " current pid: " << getpid() << std::endl;
        waitpid(pid, &status, 0);
    }

    return Process{};
}

}
}
