#include "subscriber.hpp"
#include "randomutil.hpp"

using namespace archmq;
using namespace lotus;

Subscriber::Subscriber(const std::string& mqpath)
    : _mqpath(mqpath)
    , _passcode(RandomUtil::alphabet_string_variable_length(1024, 512))
    , _status(SS_Offline)
    , _id(0)
    , _client_handle(nullptr)
    , _data_server(nullptr)
    , _master_handle(nullptr)
    , _master_server(nullptr)
{}

Subscriber::~Subscriber()
{}

std::string_view Subscriber::get_passcode() const
{
    return _passcode;
}

std::string_view Subscriber::get_mqpath() const
{
    return _mqpath;
}

void Subscriber::set_status(Subscriber::subscriber_status_e status)
{
    _status = status;
}

Subscriber::subscriber_status_e Subscriber::get_status() const
{
    return _status;
}

void Subscriber::set_id(uint32_t id)
{
    _id = id;
}

uint32_t Subscriber::get_id() const
{
    return _id;
}

void Subscriber::set_master_server_info(lotus::SocketStreamServer* master_server, lotus::oneuv::handle_t master_handle)
{
    _master_server = master_server;
    _master_handle = master_handle;
}

bool Subscriber::connect(lotus::SocketStreamServer* data_server, lotus::oneuv::handle_t client_handle)
{
    _status = SS_Online;
    _client_handle = client_handle;
    _data_server = data_server;
    return true;
}

void Subscriber::dispatch_message(lotus::Session& session, const lotus::Message& msg)
{
    Session& sess = _data_server->getornewsession(session.get_session_id(), _client_handle);

    Message transfer; // TODO: optimize the copy operation that happens here.
    transfer.im = msg.im;
    transfer.session_id = msg.session_id;
    transfer.session_payload = msg.session_payload;
    transfer.version = msg.version;
    transfer.payload = "ARCHMQ-DATA-PULSE" "\n";
    transfer.payload += msg.payload;
    
    sess.send(std::move(transfer));
}

void Subscriber::send_message(lotus::Message&& msg)
{
    Session& sess = _master_server->getornewsession(msg.session_id, _master_handle);
    sess.send(std::move(msg));
}





