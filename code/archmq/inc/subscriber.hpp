#pragma once
#include "archmq-prereq.hpp"
#include "lotus.hpp"

namespace archmq
{
    class Subscriber
    {
    public:
        enum subscriber_status_e : int
        {
            SS_Offline = 0,
            SS_Online,
            SS_Errored,
        };

    public:
        Subscriber(const std::string& mqpath);
        virtual ~Subscriber();

    public:
        std::string_view get_passcode() const;
        std::string_view get_mqpath() const;

        void set_status(subscriber_status_e status);
        subscriber_status_e get_status() const;

        void set_id(uint32_t id);
        uint32_t get_id() const;

        void set_master_server_info(lotus::SocketStreamServer* master_server, lotus::oneuv::handle_t master_handle);

        bool connect(lotus::SocketStreamServer* data_server, lotus::oneuv::handle_t client_handle);
        void dispatch_message(lotus::Session& session, const lotus::Message& msg);
        void send_message(lotus::Message&& msg);

    private:
        std::string _mqpath;
        std::string _passcode;
        subscriber_status_e _status;
        uint32_t    _id;

        lotus::oneuv::handle_t  _client_handle;
        lotus::SocketStreamServer* _data_server;

        lotus::oneuv::handle_t  _master_handle;
        lotus::SocketStreamServer* _master_server;
    };
}



