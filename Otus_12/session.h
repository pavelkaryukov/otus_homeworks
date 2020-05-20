#pragma once

//#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/format.hpp>

class Session : public std::enable_shared_from_this<Session> {
    using tcp_ip_t = boost::asio::ip::tcp;
public:

    Session(tcp_ip_t::socket aSocket)
        : m_Socket(std::move(aSocket)) {}

    void start() {
        do_read();
    }

    ~Session() {
        //Обработка состояния оставшегося
        int stop1 = 0;
    }

private:
    
    void do_read() {
        auto self(shared_from_this());
        m_Socket.async_read_some(
            boost::asio::buffer(m_Data, kMaxLength),
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    auto receivedStr = std::string{ m_Data, length };
                    m_SS << receivedStr;
                    HandleCommands();
                    std::cout << "receive " << length << "=" << receivedStr << std::endl;
                    do_write(length);
                }
            }
        );
    }

    void do_write(std::size_t aLen) {
        auto self(shared_from_this());
        std::string str = boost::str(boost::format("Accepted Msg [%1%], len = [%2%];") % std::string(m_Data, m_Data + aLen) % aLen);
        boost::asio::async_write(
            m_Socket, boost::asio::buffer(str.data(), str.size()),
            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    do_read();
                }
            }
        );
    }


    bool HandleCommands() {
        auto strMain = m_SS.str();

        std::string command;
        bool res = false;
        while (std::getline(m_SS, command)) {
            int stop1 = 0;
            res = true;
        }
        strMain = m_SS.str();
        return res;
    }

    tcp_ip_t::socket m_Socket;
    const static std::size_t kMaxLength = 1024;
    char m_Data[kMaxLength];
    std::stringstream m_SS;
};