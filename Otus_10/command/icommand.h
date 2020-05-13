#pragma once
#include <string> 
/**
* \brief  ��������� �������
*/
class IMyCommand {
protected:
    using log_text_t = std::string;
public:
    
    /**
    * \brief  ��������� �������
    * \return log_text_t - ��� ����������� ���������� �������
    */
    virtual log_text_t Execute() = 0;

    virtual ~IMyCommand() = default;
};
