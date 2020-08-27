#include "subscriber.hpp"
#include "randomutil.hpp"

using namespace archmq;
using namespace lotus;

Subscriber::Subscriber(const std::string& mqpath)
    : _mqpath(mqpath)
    , _passcode(RandomUtil::alphabet_string_variable_length(1024, 512))
    , _status(SS_Offline)
    , _client_handle(nullptr)
    , _data_server(nullptr)
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
    Message transfer(msg); // TODO: optimize the copy operation that happens here.
    sess.send(std::move(transfer));
}





