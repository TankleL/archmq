#pragma once
#include "archmq2-prereq.hpp"
#include "lotus.hpp"

namespace archmq2
{
    void ARCHMQ2_API subscribe_tcp(
        const std::string& ctrlep_ipaddr,
        const uint16_t ctrlep_port,
        const std::string& mqpath,
        const std::function<void(int /*status*/, const std::string& /*passcode*/)>& callback);

    void ARCHMQ2_API connect_data_endpoint(
        const std::string& dataep_ipaddr,
        const uint16_t dataep_port,
        const std::string& mqpath,
        const std::string& passcode,
        const std::function<void(lotus::Client& /*client*/, int /*status*/, uint32_t /*subid*/)>& connect_callback,
        const std::function<void(lotus::Client& /*client*/, lotus::Session& /*session*/, const lotus::Message& /*msg*/)>& data_callback
    );

    void ARCHMQ2_API mqloop();
}



