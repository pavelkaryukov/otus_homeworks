#pragma once
#include "command/icommand.h"
#include "dispatcher/logger.h"
#include <string> 
#include <iostream> 
//Передача логгера сделана для того что бы сохранить в лог все методы, что вызванны в процесе Execute
class SimpleCmd final : public IMyCommand {
public:
    SimpleCmd(std::string&& aName, Logger& aLogger) : m_Name(aName){
        m_Logger = std::make_shared<Logger>(aLogger);
    }

    void Execute() override {
        if (!m_Logger)
            throw std::logic_error("SimpleCmd:: m_Logger does not exist!!!");

        m_Logger->PrintOnTheScreen(m_Name);
        m_Logger->SaveInLog(m_Name);
    }
private:
    SimpleCmd() = default;

    std::string m_Name = "DefaultName";
    std::shared_ptr<Logger> m_Logger;
};

