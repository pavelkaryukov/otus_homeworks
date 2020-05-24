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
            return "Операция успешно завершена.";
            case Codes::CantInsert:
            return "Не удается вставить кортеж в таблицу.";
            case Codes::Exist:
            return "Кортеж с этим id уже существет";
            case Codes::NotExist:
            return "Кортеж с этим id не существет";
            case Codes::TableNotExist:
            return "Таблица не существует";
            case Codes::Error:
            default:
            return "Неизвестная ошибка";
        }
    }

    bool IsSucces() const {
        return m_Code == Codes::Succes;
    }
private:
    ResultCode();
    const Codes m_Code = Codes::Error;
};

