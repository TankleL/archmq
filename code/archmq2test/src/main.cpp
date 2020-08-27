#include "archmq2.hpp"
#include <iostream>

using namespace std;
using namespace archmq2;

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

    connect_data_endpoint(
        "127.0.0.1",
        18888,
        "/",
        mqpasscode,
        [](lotus::Client & client, int status) -> void {
            int c = 0;
        },
        [](lotus::Client & client, lotus::Session & session, const lotus::Message & msg) -> void {
            int c = 0;
        }
    );

    return 0;
}