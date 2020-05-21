#pragma once
#include "session.h"
#include <cctype>

class BulkServer {
    using tcp_ip_t = boost::asio::ip::tcp;
public:

    BulkServer(boost::asio::io_context& aIoContext, const std::uint16_t aPort, const std::size_t aBulkSize)
        : m_Acceptor(aIoContext, tcp_ip_t::endpoint(tcp_ip_t::v4(), aPort)) {
        m_Handler = async::connect(aBulkSize);
        do_accept();
    }

private:

    void do_accept() {
        m_Acceptor.async_accept(
            [this](boost::system::error_code ec, tcp_ip_t::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), m_Handler)->start();
            }
            do_accept();
        });
    }

    tcp_ip_t::acceptor m_Acceptor;
    async::handle_t m_Handler;
};