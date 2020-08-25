#pragma once
#include "archmq-prereq.hpp"
#include "lotus.hpp"

namespace archmq
{
    /* ****************************************************
     * @class MasterEnpoint
     * @brief singleton, acts as one of the most important
     * core components of archmq
     * ***************************************************/
    class MasterEndpoint 
    {
    private:
        MasterEndpoint();

    public:
        ~MasterEndpoint();

    public:
        static MasterEndpoint& get_intance();
        void boot();
        
    private:
        void _on_received(lotus::Session& session, const lotus::Message& msg);

    private:
        lotus::SocketStreamServer   _tcpsvr;
    };
}




