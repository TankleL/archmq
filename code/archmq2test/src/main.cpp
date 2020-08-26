#include "archmq2.hpp"
#include <iostream>

using namespace std;
using namespace archmq2;

int main(int argc, char** argv)
{
    subscribe_tcp(
        "127.0.0.1",
        8088,
        "/",
        [](int status, const std::string & passcode)-> void {
            cout << "Passcode: " << passcode << endl;
        });

    return 0;
}