#pragma once
#include "archmq-prereq.hpp"

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

        bool connect();

    private:
        std::string _mqpath;
        std::string _passcode;
        subscriber_status_e _status;
    };
}



