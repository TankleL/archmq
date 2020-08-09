#include "archmq2-api-dev-mode.hpp"
#include "mqopts.hpp"
#include "lotus.hpp"

int ARCHMQ2_API m()
{
    return 10;
}

bool ARCHMQ2_API subscribe_tcp(
    const std::string& ctrlep_ipaddr,
    const uint16_t ctrlep_port,
    const std::string& mqpath, std::string& passcode)
{
    lotus::SocketStreamClient client;

    client.set_on_connected([](lotus::Client& client) -> void {
        auto& sess = client.newsession();

    });

    client.set_session_recevied_callback([](lotus::Session & session, const lotus::Message & msg) -> void {

    });

    client.connect(lotus::SocketEndpoint(ctrlep_ipaddr, ctrlep_port));
    
    lotus::oneuv::run();
}


