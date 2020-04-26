#pragma once
#include "command/icommand.h" 
#include "command/simple_command.h"
#include "dispatcher/logger.h"
#include <string> 
#include <iostream> 
#include <deque> 
#include <boost/format.hpp>
/*! \mainpage Otus_7 (Bulk)
 *
 * \r\n  Диспетчер задач
 *
 */
/*! CommandDispatcher */
/**
* \brief  Аккумулятор  и исполнитель очереди задач
* \details задачи выполняются в статической очереди (по X штук за раз) или в динамической (блоки отделенные скобками {})
*/
class CommandDispatcher final {
public:
    /**
    * \brief  конструктор по умолчанию.
    * \details размер статической очереди - 1 команда
    */
    CommandDispatcher() = default;

    /**
    * \brief  конструктор по умолчанию
    * \details при передачи не валидного размера статической очереди - будет установлено значение по умолчанию = 1
    * \param[in] aBulkSize - размер статической очереди
    */
    CommandDispatcher(const std::size_t aBulkSize) : m_BulkSize(aBulkSize != 0 ? aBulkSize : 1) {
        if (aBulkSize == 0) {
            std::cout << boost::format("BulkSize == {%1%} - incorrect value, BulkSize was changed on {%2%}") % aBulkSize % 1 << std::endl;
        }
    }

    /**
    * \brief  метод добавляет новую команду.
    * \details 
    * \param[in] aStr - командная строка
    * - { - открыть блок
    * - } - закрыть блок
    * - команда
    */
    void ProcessCmdLine(const std::string& aStr) {
        switch (GetCmdType(aStr))
        {
        case CmdType::OpenBrace:
        {
            if (m_Status == ExecutorStatus::Static) {
                ExecuteCommands(true);
                m_Status = ExecutorStatus::Dynamic;
            }
            ++m_StartBraceCounter;
        }
        break;
        case CmdType::CloseBrace:
        {
            if (m_StartBraceCounter == 0)
                return;//Игнорируем некорректный ввод
            --m_StartBraceCounter;
            if (m_StartBraceCounter == 0) {
                ExecuteCommands(true);
                m_Status = ExecutorStatus::Static;
            }
        }
        break;
        case CmdType::Cmd:
        default:
        {
            AddCommand(std::make_unique<SimpleCommand>(aStr));
            if (m_Status == ExecutorStatus::Static)
                ExecuteCommands(false);
        }
        break;
        }
    }

    /*
    * \brief  метод выполняет все скопленные команды.
    * \details Bulck size должен быть статическим
    */
    void Flush() {
        //Не выношу в деструктор, так как при уничтожение диспетчера и нет смысла выполнять команды
        ExecuteCommands(true);
    }
private:
    enum class ExecutorStatus {
        Static,
        Dynamic
    };
    ExecutorStatus m_Status = ExecutorStatus::Static;
    std::deque<std::unique_ptr<IMyCommand>> m_Commands;
    const std::size_t m_BulkSize = 1;
    CmdLogger m_Logger;
    std::size_t m_StartBraceCounter = 0;

    void AddCommand(std::unique_ptr<IMyCommand> aCommand) {
        m_Commands.emplace_back(std::move(aCommand));
    }

    void ExecuteCommands(const bool aFlush) {
        if (m_Commands.empty())
            return;

        if (m_Status == ExecutorStatus::Static && !aFlush && m_Commands.size() < m_BulkSize)
            return;

        m_Logger.StartBulk();
        const std::size_t executedNumber = (m_Status == ExecutorStatus::Static) ? m_BulkSize : m_Commands.size();
        ExecuteNumberOfCommands(executedNumber);
        m_Logger.FinishBulk();
    }

    void ExecuteNumberOfCommands(const std::size_t aNum) {
        if (m_Commands.empty())
            return;

        const auto count = std::min(aNum, m_Commands.size());
        for (int i = 0; i < count; ++i) {
            std::string log = " ";
            log += m_Commands.front()->Execute();
            m_Commands.pop_front();
            if (i + 1 < count)
                log += ",";
            m_Logger.WriteCmd(log);
        }
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
};
