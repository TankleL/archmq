#include "subscriber.hpp"
#include "randomutil.hpp"

using namespace archmq;

Subscriber::Subscriber(const std::string& mqpath)
    : _mqpath(mqpath)
    , _passcode(RandomUtil::alphabet_string_variable_length(1024, 512))
    , _status(SS_Offline)
{}

Subscriber::~Subscriber()
{}

std::string_view Subscriber::get_passcode() const
{
    return _passcode;
}

std::string_view Subscriber::get_mqpath() const
{
    return _mqpath;
}

void Subscriber::set_status(Subscriber::subscriber_status_e status)
{
    _status = status;
}

Subscriber::subscriber_status_e Subscriber::get_status() const
{
    return _status;
}

bool Subscriber::connect()
{
    set_status(SS_Online);
    return true;
}






