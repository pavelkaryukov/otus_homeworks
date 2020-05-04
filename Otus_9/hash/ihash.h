#pragma once
#include <string> 
class IHash {
public:
    virtual void ProcessBuffer(const void* aData, const std::size_t aLen) = 0;
    virtual const std::string Result() = 0; // std::string ������� �����, ��� ��� ��� ���� ����������� �������� ��������� 
};