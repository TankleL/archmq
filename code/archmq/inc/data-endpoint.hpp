#pragma once
#include "archmq-prereq.hpp"
#include "lotus.hpp"

namespace archmq
{
    /* ****************************************************
     * @class DataEndpoint
     * @brief singleton, being used to connect archmq and
     * subscribers, push traffic messages to subcribers.
     * ***************************************************/
    class DataEndpoint
    {
    private:
        DataEndpoint();

    public:
        ~DataEndpoint();

    public:
        static DataEndpoint& get_intance();

        void boot();

    private:
        void _on_received(lotus::Session& session, const lotus::Message& msg);

    private:
        lotus::SocketStreamServer   _tcpsvr;
    };
}




