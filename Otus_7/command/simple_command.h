#pragma once
#include "command/icommand.h"
#include "dispatcher/logger.h"
#include <iostream> 

class SimpleCommand final : public IMyCommand {
public:
    SimpleCommand(const std::string&& aName) : m_Name(aName){}
    SimpleCommand(const std::string aName  ) : m_Name(aName) {}

    log_text_t Execute() override {
        return m_Name;
    }

    virtual ~SimpleCommand() = default;
private:
    SimpleCommand() = default;

    const std::string m_Name = "DefaultName";
};

