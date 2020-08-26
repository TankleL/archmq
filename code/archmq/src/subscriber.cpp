#include "subscriber.hpp"
#include "randomutil.hpp"

using namespace archmq;

Subscriber::Subscriber(const std::string& mqpath)
    : _passcode(RandomUtil::alphabet_string(128))
{}

Subscriber::~Subscriber()
{}

std::string_view Subscriber::get_passcode() const
{
    return _passcode;
}

