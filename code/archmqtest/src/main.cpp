#include "lotus.hpp"

using namespace lotus;

int main(int argc, char* argv)
{
    SocketStreamClient* client = SocketStreamClient::create();

    client->set_on_connected([](Client & client) -> void {
        Session& sess = client.newsession();

        std::cout << "Connected: Session: " << sess.get_session_id().to_string() << std::endl;

        Message msg;
        msg.im = Message::im_request;
        msg.payload = "/" "\n";
        msg.payload += "Hello lotus server!";

        sess.send(std::move(msg));
    });

    client->set_session_recevied_callback([](Session & session, const Message & msg) -> void {
        std::cout << "Received: Session: " << session.get_session_id().to_string() << std::endl;
        std::cout << "From Server: " << msg.payload;
    });

    client->connect(SocketEndpoint("127.0.0.1", 8080));

    oneuv::run();
    return 0;
}
