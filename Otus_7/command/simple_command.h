#pragma once
#include "command/icommand.h"
#include "dispatcher/logger.h"
#include <iostream> 
//�������� ������� ������� ��� ���� ��� �� ��������� � ��� ��� ������, ��� �������� � ������� Execute
class SimpleCmd final : public IMyCommand {
public:
    SimpleCmd(const std::string&& aName) : m_Name(aName){}
    SimpleCmd(const std::string aName  ) : m_Name(aName) {}

    log_text_t Execute() override {
        return m_Name;
    }
private:
    SimpleCmd() = default;

    const std::string m_Name = "DefaultName";
};

