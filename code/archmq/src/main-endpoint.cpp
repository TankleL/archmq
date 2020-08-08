#include "main-endpoint.hpp"
#include "lotus.hpp"

using namespace lotus;
using namespace archmq;

MainEndpoint::MainEndpoint()
{}

MainEndpoint::~MainEndpoint()
{}

MainEndpoint& MainEndpoint::get_intance()
{
    static MainEndpoint inst;
    return inst;
}

void MainEndpoint::boot()
{
    _tcpsvr.set_session_recevied_callback(std::bind(&MainEndpoint::_on_received, this, std::placeholders::_1, std::placeholders::_2));
    _tcpsvr.startup(SocketEndpoint("0.0.0.0", 8080), 100);
}

void MainEndpoint::_on_received(Session& session, const Message& msg)
{

}


