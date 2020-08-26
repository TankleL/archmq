#pragma once
#include "archmq-prereq.hpp"

namespace archmq
{
    class Subscriber
    {
    public:
        Subscriber(const std::string& mqpath);
        virtual ~Subscriber();

    public:
        std::string_view get_passcode() const;

    private:
        std::string _mqpath;
        std::string _passcode;
    };
}



