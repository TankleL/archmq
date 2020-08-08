#pragma once
#include "archmq-prereq.hpp"
#include "lotus.hpp"

namespace archmq
{
    /* ****************************************************
     * @class ControlEndpoint
     * @brief singleton, provides a brigde that connects
     * archmq and its subscribers.
     * ***************************************************/
    class ControlEndpoint
    {
    private:
        ControlEndpoint();

    public:
        ~ControlEndpoint();

    public:
        static ControlEndpoint& get_intance();

        void boot();

    private:
        void _on_received(lotus::Session& session, const lotus::Message& msg);

    private:
        lotus::SocketStreamServer   _tcpsvr;
    };
}




