#include "master-endpoint.hpp"
#include "lotus.hpp"

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

}


