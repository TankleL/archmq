#include "data-endpoint.hpp"
#include "globalhub.hpp"
#include "stringutil.hpp"

using namespace lotus;
using namespace archmq;

DataEndpoint::DataEndpoint()
{}

DataEndpoint::~DataEndpoint()
{}

DataEndpoint& DataEndpoint::get_intance()
{
    static DataEndpoint inst;
    return inst;
}

void DataEndpoint::boot()
{
    _tcpsvr.set_session_recevied_callback(std::bind(&DataEndpoint::_on_received, this, std::placeholders::_1, std::placeholders::_2));
    _tcpsvr.startup(SocketEndpoint("0.0.0.0", 18888), 100);
}

void DataEndpoint::_on_received(Session& session, const Message& msg)
{
    size_t offset = 0;
    auto action = StringUtil::readutil(msg.payload, '\n', 0, &offset);

    if (action == "ARCHMQ-SUBSCRIBER-CONNECT")
    {
        auto mqpath = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);
        auto passcode = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);

        bool res = _subscriber_connect(mqpath, passcode);

        Message resp;
        resp.im = Message::im_response;
        if (res)
        { // succeeded
            resp.payload = "ARCHMQ-SUBSCRIBER-CONNECT-RESP" "\n";
            resp.payload += "200";
        }
        else
        { // failed
            resp.payload = "ARCHMQ-SUBSCRIBER-CONNECT-RESP" "\n";
            resp.payload += "403";
        }

        session.send(std::move(resp));
    }
}

bool DataEndpoint::_subscriber_connect(const std::string_view& mqpath, const std::string_view& passcode)
{
    bool res = false;
    Subscriber* sub = Global::subscribercol.get(std::string(mqpath));

    if (sub != nullptr &&
        sub->get_passcode() == passcode &&
        sub->get_mqpath() == mqpath)
    {
        res = sub->connect();
    }

    return res;
}








