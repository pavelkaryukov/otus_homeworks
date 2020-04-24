#pragma once
#include "command/icommand.h" 
#include "command/simple_command.h"
#include "dispatcher/logger.h"
#include <string> 
#include <iostream> 
#include <vector> 
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

    void AddCommand(const std::string& aStr) {
        if (aStr == "{") {
            Execute();
            m_Status = ExecutorStatus::Dynamic;
        }
        else if (aStr == "}") {
            Execute();
            m_Status = ExecutorStatus::Static;
        }
        else {
            AddCommand(std::make_unique<SimpleCmd>("cmd3", m_CommandsLogger));
            if (m_Status == ExecutorStatus::Static)
                Execute();
        }
    }

private:
    ExecutorStatus m_Status = ExecutorStatus::Static;
    std::vector<std::unique_ptr<IMyCommand>> m_Commands;
    const std::size_t m_BulkSize = 1;// ≈сли bulk size == 0 -> только ручное выполнение команд ?
    Logger m_CommandsLogger;

    void AddCommand(std::unique_ptr<IMyCommand> aCommand) {
        m_Commands.emplace_back(std::move(aCommand));
        if (m_BulkSize != 0 && m_Commands.size() >= m_BulkSize) {
            Execute();
        }
    }

    void Execute() {
        for (auto& cmd : m_Commands) {
            cmd->Execute();
            std::cout << std::endl;
        }
        m_Commands.clear();
    }
};
