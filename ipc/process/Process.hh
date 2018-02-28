#pragma once

#include <functional>
#include <sys/types.h>


namespace ipc {
namespace process {

class Process 
{
    public:
        Process();
        ~Process();

    private:
        pid_t pid;

};


Process create(std::function<void()> entry_point);

}
}
