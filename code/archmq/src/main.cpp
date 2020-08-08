#include "lotus.hpp"
#include "main-endpoint.hpp"
#include "control-endpoint.hpp"

using namespace archmq;

int main(int argc, char** argv)
{
    ControlEndpoint::get_intance().boot();
    MainEndpoint::get_intance().boot();

    lotus::oneuv::run();
    return 0;
}

