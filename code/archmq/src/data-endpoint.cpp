#include "data-endpoint.hpp"
#include "globalhub.hpp"

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
    _tcpsvr.startup(SocketEndpoint("0.0.0.0", 8088), 100);
}

void DataEndpoint::_on_received(Session& session, const Message& msg)
{

}








