#include "Process.hh" 


#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

namespace ipc {
namespace process {

Process::Process(pid_t pid)
    : _pid(pid)
{
}
Process::~Process()
{
    wait(*this);
}

Process::Process(Process&& src)
{
    _pid = src._pid;
    src._pid = INVALID_PID;
}

Process& Process::operator=(Process&& src)
{
    _pid = src._pid;
    src._pid = INVALID_PID;
    return *this;
}


Process create(std::function<void()> entry_point)
{
    pid_t pid = fork();

    switch(pid){
        case Process::INVALID_PID:
            std::cerr << "Error: cannot create process" << std::endl;
        case Process::CHILD_PID:
            entry_point();
            break;
        default:
            ;
    }

    return Process{pid};
}

namespace{
    bool is_waiting_needed(const pid_t& pid)
    {
        return Process::INVALID_PID != pid 
            && Process::CHILD_PID != pid;
    }
}


void wait(Process& proc)
{
    if(true == is_waiting_needed(proc._pid))
    {
        int status = 0;
        waitpid(proc._pid, &status, 0);
        proc._pid = Process::INVALID_PID;
    }
}

}
}
