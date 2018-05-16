#include "Logging.hh"

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <algorithm>


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

logger& operator<<( logger& l, const unsigned long ul)
{
    l.ss << ul;
    return l;
}


namespace
{
    auto get_current_time()
    {
        auto now = std::chrono::system_clock::now();
        return std::chrono::system_clock::to_time_t(now);
    }
}


logger& operator<< ( logger& l, const end_type& )
{
    auto time = get_current_time();
    std::string time_str = std::ctime(&time);
    time_str.erase(std::remove(time_str.begin(), time_str.end(), '\n'), time_str.end());
    
    auto thread_id = std::this_thread::get_id();

    std::cout << time_str << " Pid: " << getpid() << ", thread: "<< thread_id << " " << l.ss.str() << std::endl;
    l.ss.str(std::string());
    return l;
}
}
