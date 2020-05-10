#pragma once
#include "command/icommand.h" 
#include "command/simple_command.h"
#include "logger/logger.h"
#include <string> 
#include <iostream> 
#include <deque> 
#include <boost/format.hpp>
/*! \mainpage Otus_7 (Bulk)
 *
 * \r\n  ��������� �����
 *
 */
/*! CommandDispatcher */
/**
* \brief  �����������  � ����������� ������� �����
* \details ������ ����������� � ����������� ������� (�� X ���� �� ���) ��� � ������������ (����� ���������� �������� {})
*/
class CommandDispatcher {
public:
    /**
    * \brief  ����������� �� ���������.
    * \details ������ ����������� ������� - 1 �������
    */
    CommandDispatcher() = default;

    /**
    * \brief  ����������� �� ���������
    * \details ��� �������� �� ��������� ������� ����������� ������� - ����� ����������� �������� �� ��������� = 1
    * \param[in] aBulkSize - ������ ����������� �������
    */
    CommandDispatcher(const std::size_t aBulkSize, std::ostream& aStream = std::cout) : m_BulkSize(aBulkSize != 0 ? aBulkSize : 1), m_Logger({ aStream }) {
        if (aBulkSize == 0) {
            std::cout << boost::format("BulkSize == {%1%} - incorrect value, BulkSize was changed on {%2%}") % aBulkSize % 1 << std::endl;
        }
    }

    /**
    * \brief  ����� ��������� ����� �������.
    * \details 
    * \param[in] aStr - ��������� ������
    * - { - ������� ����
    * - } - ������� ����
    * - �������
    */
    void ProcessCmdLine(const std::string& aStr) {
        ++_lines;
        switch (GetCmdType(aStr))
        {
        case CmdType::OpenBrace:
            ProcessOpenBrace();
            break;
        case CmdType::CloseBrace:
            ProcessCloseBrace();
            break;
        case CmdType::Cmd:
        default:
            ProcessCmd(aStr);
            break;
        }
    }

    /**
    * \brief  ����� ��������� ��� ���������� �������.
    * \details Bulk size ������ ���� �����������
    */
    void Flush() {
        //�� ������ � ����������, ��� ��� ��� ����������� ���������� � ��� ������ ��������� �������
        ExecuteCommands(true);
    }

    ~CommandDispatcher() {
        m_Logger.Exit();
        PrintStat();
    }
private:
    enum class ExecutorStatus {
        Static,
        Dynamic
    };
    ExecutorStatus m_Status = ExecutorStatus::Static;
    std::deque<std::unique_ptr<IMyCommand>> m_Commands;
    const std::size_t m_BulkSize = 1;
    std::size_t m_StartBraceCounter = 0;
    CmdLogger m_Logger;

    std::size_t _lines    = 0;
    std::size_t _bulks    = 0;
    std::size_t _commands = 0;


    void AddCommand(std::unique_ptr<IMyCommand> aCommand) {
        m_Commands.emplace_back(std::move(aCommand));
    }

    void ExecuteCommands(const bool aFlush) {
        if (m_Commands.empty())
            return;

        if (m_Status == ExecutorStatus::Static && !aFlush && m_Commands.size() < m_BulkSize)
            return;

        const std::size_t executedNumber = (m_Status == ExecutorStatus::Static) ? m_BulkSize : m_Commands.size();
        ExecuteNumberOfCommands(executedNumber);
    }

    void ExecuteNumberOfCommands(const std::size_t aNum) {
        if (m_Commands.empty())
            return;

        const auto count = std::min(aNum, m_Commands.size());
        ++_bulks;
        std::string logStr = "bulk: ";
        for (std::size_t i = 0; i < count; ++i) {
            ++_commands;
            logStr += m_Commands.front()->Execute();
            m_Commands.pop_front();
            if (i + 1 < count)
                logStr += ", ";
        }
        m_Logger.Save(logStr, count);
    }

    enum class CmdType {
        OpenBrace,
        CloseBrace,
        Cmd
    };

    CmdType GetCmdType(const std::string aStr) {
        if (aStr == "{")
            return CmdType::OpenBrace;
        else if (aStr == "}")
            return CmdType::CloseBrace;
        else
            return CmdType::Cmd;
    }

    void ProcessOpenBrace() {
        if (m_Status == ExecutorStatus::Static) {
            ExecuteCommands(true);
            m_Status = ExecutorStatus::Dynamic;
        }
        ++m_StartBraceCounter;
    }

    void ProcessCloseBrace() {
        if (m_StartBraceCounter == 0)
            return;//���������� ������������ ����
        --m_StartBraceCounter;
        if (m_StartBraceCounter == 0) {
            ExecuteCommands(true);
            m_Status = ExecutorStatus::Static;
        }
    }

    void ProcessCmd(const std::string& aStr) {
        AddCommand(std::make_unique<SimpleCommand>(aStr));
        if (m_Status == ExecutorStatus::Static)
            ExecuteCommands(false);
    }

    void PrintStat() {
        m_Logger.PrintStat(_lines, _bulks, _commands);
    }
};
