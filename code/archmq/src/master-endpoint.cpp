#include "master-endpoint.hpp"
#include "lotus.hpp"
#include "stringutil.hpp"
#include "globalhub.hpp"

using namespace lotus;
using namespace archmq;

MasterEndpoint::MasterEndpoint()
{}

MasterEndpoint::~MasterEndpoint()
{}

MasterEndpoint& MasterEndpoint::get_intance()
{
    static MasterEndpoint inst;
    return inst;
}

void MasterEndpoint::boot()
{
    _tcpsvr.set_session_recevied_callback(std::bind(&MasterEndpoint::_on_received, this, std::placeholders::_1, std::placeholders::_2));
    _tcpsvr.startup(SocketEndpoint("0.0.0.0", 8080), 100);
}

void MasterEndpoint::_on_received(Session& session, const Message& msg)
{
    size_t offset = 0;
    auto mqpath = StringUtil::readutil(msg.payload, '\n', 0, &offset);

    Subscriber* sub = Global::subscribercol.get(std::string(mqpath));
    if (sub != nullptr)
    {
        sub->set_master_server_info(&_tcpsvr, session.get_localstate_refinable_ptr(SESS_LS_CONN_STREAM_HANDLE_IDX));
        sub->dispatch_message(session, msg);
    }
    else
    { // TODO: error handling
        session.add_control_bit(Session::scb_end_connection);

        Message resp;
        resp.im = Message::im_response;
        resp.payload = "404";

        session.send(std::move(resp));
    }
}


