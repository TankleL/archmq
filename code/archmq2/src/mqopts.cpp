#include "archmq2-api-dev-mode.hpp"
#include "mqopts.hpp"
#include "lotus.hpp"
#include "stringutil.hpp"

using namespace lotus;
using namespace archmq2;

void ARCHMQ2_API archmq2::subscribe_tcp(
    const std::string& ctrlep_ipaddr,
    const uint16_t ctrlep_port,
    const std::string& mqpath,
    const std::function<void(int /*status*/, const std::string& /*passcode*/)>& callback)
{
    SocketStreamClient* client = SocketStreamClient::create();

    client->set_on_connected([=](lotus::Client& client) -> void {
        auto& sess = client.newsession();
        sess.add_control_bit(Session::scb_end_connection);

        Message msg;
        msg.im = Message::im_request;
        msg.payload = "ARCHMQ-SUBSCRIBE" "\n"; // [Param 1] action
        msg.payload += mqpath;                 // [Param 2] message queue path

        sess.send(std::move(msg));
    });

    client->set_session_recevied_callback([=](lotus::Session & session, const lotus::Message & msg) -> void {
        assert(msg.im == Message::im_response);

        size_t offset = 0;
        auto opt = StringUtil::readutil(msg.payload, '\n', 0, &offset);

        if (opt == "ARCHMQ-SUBSCRIBE-RESP")
        {
            auto passcode = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);
            callback(200, std::string(passcode));
        }
        else
        {
            callback(400, "");
        }
    });

    client->connect(lotus::SocketEndpoint(ctrlep_ipaddr, ctrlep_port));
    
    lotus::oneuv::run();
}


