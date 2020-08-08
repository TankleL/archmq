#pragma once
#include "archmq-prereq.hpp"
#include "lotus.hpp"

namespace archmq
{
    /* ****************************************************
     * @class MainEnpoint
     * @brief singleton, acts as one of the most important
     * core components of archmq
     * ***************************************************/
    class MainEndpoint
    {
    private:
        MainEndpoint();

    public:
        ~MainEndpoint();

    public:
        static MainEndpoint& get_intance();
        void boot();
        
    private:
        void _on_received(lotus::Session& session, const lotus::Message& msg);

    private:
        lotus::SocketStreamServer   _tcpsvr;
    };
}




