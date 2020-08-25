#pragma once
#include "archmq-prereq.hpp"
#include "subscriber.hpp"

namespace archmq
{
    class SubscriberCollection
    {
    public:
        typedef std::unordered_map<std::string, std::unique_ptr<Subscriber>>
            subscribers_map_t;

    public:
        void add(const std::string& mqpath, std::unique_ptr<Subscriber>&& subscriber);
        Subscriber* get(const std::string& mqpath) const;

    private:
        subscribers_map_t _subscribersmap;
    };
}




