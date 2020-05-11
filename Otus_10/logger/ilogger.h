#pragma once
#include <cctype>

class ILogger {
    struct Stat {
        std::size_t Commands = 0;
        std::size_t Bulks = 0;

        void Add(const std::size_t aCommands) {
            Commands += aCommands;
            Bulks += 1;
        }
    };
public:
    void Output(std::string aStr, const std::size_t aCommands) {
        m_Statistic.Add(aCommands);
        SaveLog(aStr);
    }

    //по окончанию использования выйти
    virtual void Exit() = 0;

    virtual ~ILogger() {}

    const Stat GetStat() {
        return m_Statistic;
    }
private:
    //после подсчета статистики сохранение лога выполняет этот метод
    virtual void SaveLog(std::string aStr) = 0;
    Stat m_Statistic = {};
};

