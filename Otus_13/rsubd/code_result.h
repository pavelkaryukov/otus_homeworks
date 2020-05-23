#pragma once
#include <string>


class ResultCode {
public:       
    enum class Codes {
        Succes,
        CantInsert,
        Exist,
        NotExist,
        TableNotExist,
        Error
    };
    ResultCode(const Codes aCode) : m_Code(aCode) {}

    std::string What() const {
        switch (m_Code) {
            case Codes::Succes:
            return "�������� ������� ���������.";
            case Codes::CantInsert:
            return "�� ������� �������� ������ � �������.";
            case Codes::Exist:
            return "������ � ���� id ��� ���������";
            case Codes::NotExist:
            return "������ � ���� id �� ���������";
            case Codes::Error:
            default:
            return "����������� ������";
        }
    }

    bool IsSucces() const {
        return m_Code == Codes::Succes;
    }
private:
    ResultCode();
    const Codes m_Code = Codes::Error;
};

