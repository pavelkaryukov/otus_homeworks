#pragma once
#include "command/icommand.h" 
#include "command/simple_command.h"
#include "dispatcher/logger.h"
#include <string> 
#include <iostream> 
#include <deque> 
#include <boost/format.hpp>

enum class ExecutorStatus {
    Static,
    Dynamic
};

class CommandDispatcher {
public:
    CommandDispatcher() = default;

    CommandDispatcher(const std::size_t aBulkSize) : m_BulkSize(aBulkSize != 0 ? aBulkSize : 1) {
        if (aBulkSize == 0) {
            std::cout << boost::format("BulkSize == {%1%} - incorrect value, BulkSize was changed on {%2%}") % aBulkSize % 1 << std::endl;
        }
    }

    void ProcessCmdLine(const std::string& aStr) {// Разбить на методы ?
        if (aStr == "{") {
            if (m_Status == ExecutorStatus::Static) {
                ExecuteCommands(true);
                m_Status = ExecutorStatus::Dynamic;
            } 
            ++m_StartBraceCounter;
        }
        else if (aStr == "}") {
            if (m_StartBraceCounter == 0)
                return;//Игнорируем некорректный ввод
            --m_StartBraceCounter;
            if (m_StartBraceCounter == 0) {
                ExecuteCommands(true);
                m_Status = ExecutorStatus::Static;
            }
        }
        else {
            ProcessCmdLine(std::make_unique<SimpleCmd>(std::string(aStr), m_CommandsLogger));
            if (m_Status == ExecutorStatus::Static)
                ExecuteCommands(false);
        }
    }

private:
    ExecutorStatus m_Status = ExecutorStatus::Static;
    std::deque<std::unique_ptr<IMyCommand>> m_Commands;
    const std::size_t m_BulkSize = 1;// Если bulk size == 0 -> только ручное выполнение команд ?
    Logger m_CommandsLogger;
    std::size_t m_StartBraceCounter = 0;

    void ProcessCmdLine(std::unique_ptr<IMyCommand> aCommand) {
        m_Commands.emplace_back(std::move(aCommand));
    }

    void ExecuteCommands(const bool aFlush) {
        if (m_Commands.empty())
            return;

        if (m_Status == ExecutorStatus::Static && !aFlush && m_Commands.size() < m_BulkSize)
            return;

        m_CommandsLogger.StartBulk();

        switch (m_Status) {
            case ExecutorStatus::Dynamic:
                ExecuteDynamic();
                break;
            case ExecutorStatus::Static:
                ExecuteStatic();
                break;
        }

        m_CommandsLogger.FinishBulk();
    }

    void ExecuteStatic() {
        if (m_Commands.empty())
            return;
        const auto count = std::min(m_BulkSize, m_Commands.size());

        for (int i = 0; i < count; ++i) {
            m_Commands.front()->Execute();
            m_Commands.pop_front();
        }
    }

    void ExecuteDynamic() {
        for (auto& cmd : m_Commands) {
            cmd->Execute();
        }
        m_Commands.clear();
    }
};
