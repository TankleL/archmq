#pragma once

#include "archmq-prereq.hpp"

namespace archmq
{
    class Subscriber
    {
    public:
        Subscriber(const std::string& mqpath);
        virtual ~Subscriber();

    private:
        std::string _mqpath;
        std::string _passcode;
    };
}



