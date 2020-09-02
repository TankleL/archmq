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

    if (action == "ARCHMQ-SUBSCRIBER-SENDMSG")
    {
        auto subid = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);
        uint32_t id = atoi(std::string(subid).c_str());
        Subscriber* sub = Global::subscribercol.get(id);

        if (sub != nullptr)
        {
            auto payload = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);
                
            Message transfer;
            transfer.im = msg.im;
            transfer.session_id = msg.session_id;
            transfer.session_payload = msg.session_payload;
            transfer.version = msg.version;
            transfer.payload = std::string(payload);

            sub->send_message(std::move(transfer));
        }
        else
        { // TODO: error handling
        }
    }
    else if (action == "ARCHMQ-SUBSCRIBER-CONNECT")
    {
        auto mqpath = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);
        auto passcode = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);

        bool res = _subscriber_connect(
            mqpath,
            passcode,
            session.get_localstate_refinable_ptr(SESS_LS_CONN_STREAM_HANDLE_IDX));

        Message resp;
        resp.im = Message::im_response;
        if (res)
        { // succeeded
            std::ostringstream oss;
            oss << "ARCHMQ-SUBSCRIBER-CONNECT-RESP" "\n";
            oss << "200" "\n";
            oss << Global::subscribercol.get(std::string(mqpath))->get_id();

            resp.payload = oss.str();
        }
        else
        { // failed
            resp.payload = "ARCHMQ-SUBSCRIBER-CONNECT-RESP" "\n";
            resp.payload += "403";
        }

        session.send(std::move(resp));
    }
}

bool DataEndpoint::_subscriber_connect(
    const std::string_view& mqpath,
    const std::string_view& passcode,
    lotus::oneuv::handle_t client_handle)
{
    bool res = false;
    Subscriber* sub = Global::subscribercol.get(std::string(mqpath));

    if (sub != nullptr &&
        sub->get_passcode() == passcode &&
        sub->get_mqpath() == mqpath)
    {
        res = sub->connect(&_tcpsvr, client_handle);
    }

    return res;
}








