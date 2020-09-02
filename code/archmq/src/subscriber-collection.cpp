#include "subscriber-collection.hpp"

using namespace archmq;

SubscriberCollection::SubscriberCollection()
    : _topid(0)
{}

void SubscriberCollection::add(const std::string& mqpath, std::unique_ptr<Subscriber>&& subscriber)
{
    subscriber->set_id(_topid++);
    _subscribersidmap[subscriber->get_id()] = subscriber.get();
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

Subscriber* SubscriberCollection::get(uint32_t id) const
{
    const auto& sub = _subscribersidmap.find(id);
    if (sub != _subscribersidmap.cend())
    {
        return sub->second;
    }
    return nullptr;
}



