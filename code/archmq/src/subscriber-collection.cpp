#include "subscriber-collection.hpp"

using namespace archmq;

void SubscriberCollection::add(const std::string& mqpath, std::unique_ptr<Subscriber>&& subscriber)
{
    _subscribersmap[mqpath] = std::move(subscriber);
}

Subscriber* SubscriberCollection::get(const std::string& mqpath) const
{
    const auto& sub = _subscribersmap.find(mqpath);
    if (sub != _subscribersmap.cend())
    {
        return sub->second.get();
    }
    return nullptr;
}



