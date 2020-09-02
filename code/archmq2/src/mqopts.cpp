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


void ARCHMQ2_API archmq2::connect_data_endpoint(
    const std::string& dataep_ipaddr,
    const uint16_t dataep_port,
    const std::string& mqpath,
    const std::string& passcode,
    const std::function<void(lotus::Client& /*client*/, int /*status*/, uint32_t /*subid*/)>& connect_callback,
    const std::function<void(lotus::Client& /*client*/, lotus::Session& /*session*/, const lotus::Message& /*msg*/)>& data_callback)
{
    SocketStreamClient* client = SocketStreamClient::create(true);

    client->set_on_connected([=](lotus::Client & client) -> void {
        auto& sess = client.newsession();
        sess.add_control_bit(Session::scb_keep_session);

        Message msg;
        msg.im = Message::im_request;
        msg.payload = "ARCHMQ-SUBSCRIBER-CONNECT" "\n";
        msg.payload += mqpath + "\n";
        msg.payload += passcode;

        sess.send(std::move(msg));
    });

    client->set_session_recevied_callback([=](lotus::Session & session, const lotus::Message & msg) -> void {
        size_t offset = 0;
        auto action = StringUtil::readutil(msg.payload, '\n', 0, &offset);

        if (action == "ARCHMQ-DATA-PULSE")
        {
            data_callback(*client, session, msg);
        }
        else if(action == "ARCHMQ-SUBSCRIBER-CONNECT-RESP")
        {
            auto status = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);
            auto subid = StringUtil::readutil(msg.payload, '\n', offset + 1, &offset);

            connect_callback(
                *client,
                atoi(std::string(status).c_str()),
                atoi(std::string(subid).c_str()));
        }
        else
        { // TODO: handle errors
        }
    });

    client->connect(lotus::SocketEndpoint(dataep_ipaddr, dataep_port));

    lotus::oneuv::run();

}


