#pragma once
#include "archmq-prereq.hpp"
#include "subscriber.hpp"

namespace archmq
{
    class SubscriberCollection
    {
    public:
        void add(std::unique_ptr<Subscriber>&& subscriber);
        Subscriber* get(const std::string& mqpath) const;

    private:
    };
}




