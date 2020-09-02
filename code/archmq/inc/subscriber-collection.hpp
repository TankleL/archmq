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
        typedef std::unordered_map<uint32_t, Subscriber*> subscribers_id_map_t;

    public:
        SubscriberCollection();

    public:
        void add(const std::string& mqpath, std::unique_ptr<Subscriber>&& subscriber);
        Subscriber* get(const std::string& mqpath) const;
        Subscriber* get(uint32_t id) const;

    private:
        subscribers_map_t _subscribersmap;
        subscribers_id_map_t _subscribersidmap;

        uint32_t _topid;
    };
}




