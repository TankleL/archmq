#include "lotus.hpp"
#include "master-endpoint.hpp"
#include "control-endpoint.hpp"
#include "data-endpoint.hpp"

using namespace archmq;

int main(int argc, char** argv)
{
    ControlEndpoint::get_intance().boot();
    DataEndpoint::get_intance().boot();
    MasterEndpoint::get_intance().boot();

    lotus::oneuv::run();
    return 0;
}

