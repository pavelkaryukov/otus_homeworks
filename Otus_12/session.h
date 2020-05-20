#pragma once
#include "bulk_async.h"
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/format.hpp>

class Session : public std::enable_shared_from_this<Session> {
    using tcp_ip_t = boost::asio::ip::tcp;
    enum class CmdType {
        open,
        close,
        regular
    };
public:

    Session(tcp_ip_t::socket aSocket, const async::handle_t aGeneralHandler)
        : m_Socket(std::move(aSocket)), m_GeneralHandler(aGeneralHandler) {
    }

    void start() {
        do_read();
    }

    ~Session() {
        ProcessAllCommands();
        if (m_UniqueHandler)
            async::disconnect(m_UniqueHandler);
    }

private:
    
    void do_read() {
        auto self(shared_from_this());
        m_Socket.async_read_some(
            boost::asio::buffer(m_Data, kMaxLength),
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    m_AllCmds += std::string{ m_Data, length };//важный момент, нарезка сообщений осуществляется по \n
                    ProcessAllCommands();
                    auto receivedStr = std::string{ m_Data, length };
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

    void ProcessAllCommands() {
        //TCP протокол потоко ориентированный, потому, так как возможна фрагметация хоть по байту,
        //мы нарезаем сообщения по символ перевода строки
        auto beginPos = m_AllCmds.begin();
        auto endPos = m_AllCmds.find('\n');
        while (endPos != std::string::npos && beginPos < m_AllCmds.end()){
            const auto myStr = std::string(beginPos, m_AllCmds.begin() + endPos);
            ProcessCommand(myStr);
            beginPos = m_AllCmds.begin() + endPos + 1;
            endPos = m_AllCmds.find('\n', beginPos - m_AllCmds.begin());
        }
        if (beginPos >= m_AllCmds.end())
            m_AllCmds.clear();
        else
            m_AllCmds.erase(m_AllCmds.begin(), beginPos);
    }

    CmdType GetCmdType(std::string& aStr) {
        if (aStr == "{") {
            return CmdType::open;
        }
        else if (aStr == "}") {
            return CmdType::close;
        }
        else {
            return CmdType::regular;
        }
    }

    void ProcessCommand(std::string aStr) {
        const auto cmdType = GetCmdType(aStr);
        switch (cmdType) {
            case CmdType::open:
                ++m_BraceCounter;
                UseUniqueHandler(aStr);
                break;
            case CmdType::close:
                --m_BraceCounter;
                UseUniqueHandler(aStr);
            break;
            case CmdType::regular:
                (m_BraceCounter != 0) ? UseUniqueHandler(aStr) : UseGeneralHandler(aStr);
            break;
        }
    }

    void UseUniqueHandler(const std::string aStr) {
        if (m_UniqueHandler == 0) //Ленивая инициализация
            m_UniqueHandler = async::connect(3);//Уникальные обработчики используются только для обработки динамических сообщений, стало быть размер балка не важен
        async::receive(m_UniqueHandler, aStr.data(), aStr.size());
    }

    void UseGeneralHandler(const std::string aStr) {
        async::receive(m_GeneralHandler, aStr.data(), aStr.size());
    }

    tcp_ip_t::socket m_Socket;
    const static std::size_t kMaxLength = 1024;
    char m_Data[kMaxLength];
    const async::handle_t m_GeneralHandler = 0;
    async::handle_t m_UniqueHandler = 0;
    std::size_t m_BraceCounter = 0;
    std::string m_AllCmds;
};