#pragma once
#include "dispatcher/dispatcher.h"
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

class  Session : public std::enable_shared_from_this<Session> {
    using tcp_ip_t = boost::asio::ip::tcp;
public:
    Session(tcp_ip_t::socket aSocket, std::shared_ptr<DispatherSUBD> aDispatcher)
        : m_Socket(std::move(aSocket)), m_Dispatcher(aDispatcher) {}
    
    void start() {
        do_read();
    }

    ~Session() {
        ProcessAllCommands();
    }
private:
    
    void do_read() {
        auto self(shared_from_this());
        m_Socket.async_read_some(
            boost::asio::buffer(m_Data, kMaxLength),
            [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                m_AllCmds += std::string{ m_Data, length };//важный момент, нарезка сообщений осуществл¤етс¤ по \n
                ProcessAllCommands();
                do_read();
            }
        }
        );
    }

    void ProcessAllCommands() {
        //TCP протокол потоко ориентированный, потому, так как возможна фрагметаци¤ хоть по байту,
        //мы нарезаем сообщени¤ по символ перевода строки
        auto beginPos = m_AllCmds.begin();
        auto endPos = m_AllCmds.find('\n');
        while (endPos != std::string::npos && beginPos < m_AllCmds.end()) {
            const auto myStr = std::string(beginPos, m_AllCmds.begin() + endPos);
            if (m_Dispatcher)
                m_Dispatcher->ProcessCommand(myStr);
            beginPos = m_AllCmds.begin() + endPos + 1;
            endPos = m_AllCmds.find('\n', beginPos - m_AllCmds.begin());
        }
        if (beginPos >= m_AllCmds.end())
            m_AllCmds.clear();
        else
            m_AllCmds.erase(m_AllCmds.begin(), beginPos);
    }

    tcp_ip_t::socket m_Socket;
    static const std::size_t kMaxLength = 1024;
    char m_Data[kMaxLength];
    std::string m_AllCmds;
    std::shared_ptr<DispatherSUBD> m_Dispatcher;
};
