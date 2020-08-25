#include "control-endpoint.hpp"
#include "globalhub.hpp"
#include "stringutil.hpp"

using namespace lotus;
using namespace archmq;

ControlEndpoint::ControlEndpoint()
{}

ControlEndpoint::~ControlEndpoint()
{}

ControlEndpoint& ControlEndpoint::get_intance()
{
    static ControlEndpoint inst;
    return inst;
}

void ControlEndpoint::boot()
{
    _tcpsvr.set_session_recevied_callback(std::bind(&ControlEndpoint::_on_received, this, std::placeholders::_1, std::placeholders::_2));
    _tcpsvr.startup(SocketEndpoint("0.0.0.0", 8088), 100);
}

void ControlEndpoint::_on_received(Session& session, const Message& msg)
{
    
    size_t offset = 0;
    std::string_view action = StringUtil::readutil(msg.payload, '\n', 0, &offset);

    if (action == "ARCHMQ-SUBSCRIBE")
    {
        std::string_view mqpath = StringUtil::readutil(msg.payload, '\n', offset, &offset);

        auto sub = std::make_unique<Subscriber>(std::string(mqpath));
        Global::subscribercol.add(std::string(mqpath), std::move(sub));
    }
}







