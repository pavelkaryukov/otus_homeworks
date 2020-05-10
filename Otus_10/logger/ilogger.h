#pragma once

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
        _stat.Add(aCommands);
        SaveLog(aStr);
    }

    virtual void Exit() = 0;

    virtual ~ILogger() {}

    const Stat GetStat() {
        return _stat;
    }
private:
    virtual void SaveLog(std::string aStr) = 0;
    Stat _stat = {};
};

