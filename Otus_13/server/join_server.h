#pragma once
#include "server/session.h"
class JoinServer {
    using tcp_ip_t = boost::asio::ip::tcp;

public:

    JoinServer
    (
        boost::asio::io_context& aIoContext, 
        const std::uint16_t aPort, 
        std::shared_ptr<std::mutex> aMutex, 
        std::ostream& aStream
    ) : m_Acceptor(aIoContext, tcp_ip_t::endpoint(tcp_ip_t::v4(), aPort)),  m_Dispatcher(std::make_shared<DispatherSUBD>(aStream, aMutex))
    {
        do_accept();
    }

private:

    void do_accept() {
        m_Acceptor.async_accept(
            [this](boost::system::error_code ec, tcp_ip_t::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), m_Dispatcher)->start();
            }
            do_accept();
        });
    }

    tcp_ip_t::acceptor m_Acceptor;
    std::shared_ptr<DispatherSUBD> m_Dispatcher = nullptr;
};