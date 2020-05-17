#pragma once
#include "lib/command/icommand.h"
#include "lib/logger/logger.h"
#include <iostream> 
/**
* \brief   ���������� ������������� ���������� IMyCommand
* \details ��� ���������� ���������� ���� ���
*/
class SimpleCommand final : public IMyCommand {
public:
    SimpleCommand(const log_text_t&& aName) : m_Name(std::move(aName)){}
    SimpleCommand(const log_text_t aName  ) : m_Name(aName) {}

    log_text_t Execute() override {
        return m_Name;
    }

    virtual ~SimpleCommand() = default;
private:
    SimpleCommand() = default;

    const log_text_t m_Name = "DefaultName";
};

