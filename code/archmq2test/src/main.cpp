#include "archmq2.hpp"
#include <iostream>
#include <sstream>

using namespace std;
using namespace archmq2;
using namespace lotus;

int main(int argc, char** argv)
{
    std::string mqpasscode;

    subscribe_tcp(
        "127.0.0.1",
        8088,
        "/",
        [&](int status, const std::string & passcode)-> void {
            cout << "Passcode: " << passcode << endl;
            mqpasscode = passcode;
        });

    uint32_t subscriber_id = -1;

    connect_data_endpoint(
        "127.0.0.1",
        18888,
        "/",
        mqpasscode,
        [&](lotus::Client & client, int status, uint32_t subid) -> void {
            if (status == 200)
            {
                subscriber_id = subid;
            }
            else
            { // TODO: error handling
            }
        },
        [&](lotus::Client & client, lotus::Session & session, const lotus::Message & msg) -> void {
            std::ostringstream oss;
            oss << "ARCHMQ-SUBSCRIBER-SENDMSG" "\n";
            oss << subscriber_id << "\n";
            oss << "Hi, this is a response from a server using arch mq.";

            Message resp;
            resp.im = Message::im_response;
            resp.payload = oss.str();

            session.send(std::move(resp));
        }
    );

    return 0;
}