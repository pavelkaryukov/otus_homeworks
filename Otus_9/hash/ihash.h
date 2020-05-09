#pragma once
#include <string> 
/**
* \brief  ��������� ������� ������� ��� �������
*/
class IHash {
public:
    /**
    * \brief ������� ������ ��� ������� ��� �������
    * \param[in] aData - ��������� �� ������ ������
    * \param[in] aLen - ����� ������� � ������
    */    
    virtual void ProcessBuffer(const void* aData, const std::size_t aLen) = 0;
    
    /**
    * \brief  �������� ������������ ������ ��� �������
    * \details ���������� ��������� ���������� ��� ������ (� ����������� �� ���������� ������ ����������) ������� ��� �����
    * \return std::string - ��� ����� �������������� ����� ������
    */
    virtual const std::string Result() = 0; // std::string ������� �����, ��� ��� ��� ���� ����������� �������� ��������� 
};