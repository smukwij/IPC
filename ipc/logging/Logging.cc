#include "Logging.hh"

#include <sys/types.h>
#include <unistd.h>
#include <iostream>

namespace ipc {
namespace logging 
{


logger& operator<<( logger& l, const std::string& message)
{
    l.ss << message;
    return l;
}

logger& operator<<( logger& l, const double d)
{
    l.ss << d;
    return l;
}

logger& operator<<( logger& l, const int i)
{
    l.ss << i;
    return l;
}

logger& operator<< ( logger& l, const end_type& )
{
    const std::string time {"place for time"};
    std::cout << time << " Pid: " << getpid() << " " << l.ss.str() << std::endl;
    l.ss.str(std::string());
    return l;
}
}
}
