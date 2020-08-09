#pragma once
#include "archmq2-prereq.hpp"

int ARCHMQ2_API m();

bool ARCHMQ2_API subscribe_tcp(
    const std::string& ctrlep_ipaddr,
    const uint16_t ctrlep_port,
    const std::string& mqpath, std::string& passcode);



