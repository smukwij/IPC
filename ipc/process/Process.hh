#pragma once

#include <functional>
#include <sys/types.h>


namespace ipc {
namespace process {

class Process 
{
    public:
        enum 
        {
            INVALID_PID = -1,
            CHILD_PID = 0
        };

        ~Process();
        Process(const Process&) = delete;
        Process(Process&&);

        Process& operator=(Process) = delete;
        Process& operator=(Process&&);


    private:
        friend Process create(std::function<void()> entry_point);
        friend void wait(Process&);

        explicit Process(pid_t pid);
        pid_t _pid;
};


Process create(std::function<void()> entry_point);
void wait(Process&);
}
}
