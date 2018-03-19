#pragma once
#include <string>
#include <sstream>

namespace ipc {
namespace logging 
{

struct end
{
};

struct logger
{

    private:

        friend logger& operator<<( logger& l, const std::string& message);
        friend logger& operator<<( logger& l, const double d);
        friend logger& operator<<( logger& l, const int i);


        
        friend logger& operator<<( logger& l, const end&);

        std::stringstream ss;
};

static logger log_info;
static logger log_err;



logger& operator<<( logger& l, const std::string& message);

logger& operator<<( logger& l, const double d);

logger& operator<<( logger& l, const int i);

logger& operator<< ( logger& l, const end& );
}
}
