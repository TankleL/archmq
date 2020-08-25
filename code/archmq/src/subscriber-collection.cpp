#include "subscriber-collection.hpp"

using namespace archmq;

void SubscriberCollection::add(const std::string& mqpath, std::unique_ptr<Subscriber>&& subscriber)
{
    _subscribersmap[mqpath] = std::move(subscriber);
}



