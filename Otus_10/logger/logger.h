#pragma once       
#include "logger/logger_screen.h"
#include "logger/logger_file.h"
#include <string> 

class CmdLogger {
public:
    CmdLogger(std::ostream& aStream) {
        _loggerScreen = std::make_unique<LoggerScreen>(aStream, _screenMutex);
        _loggerFile1 = std::make_unique<LoggerFile>();
        _loggerFile2 = std::make_unique<LoggerFile>();
    }

    void Save(const std::string aStr, const std::size_t aCommandsNum) {
        ++_counterBulk;
        _ñounterCommands += aCommandsNum;
        if (_loggerScreen)
            _loggerScreen->Output(aStr, aCommandsNum);

        SaveInFile((_counterBulk % 2 == 1) ? _loggerFile1 : _loggerFile2, aStr, aCommandsNum);
    }

    void Exit() {
        if (_loggerScreen)
            _loggerScreen->Exit();
        
        if (_loggerFile1)
            _loggerFile1->Exit();

        if (_loggerFile2)
            _loggerFile2->Exit();
    }

    ~CmdLogger() {}

    void PrintStat(const std::size_t aLines, const std::size_t aBulks, const std::size_t aCommands) {
        {
            std::lock_guard<std::mutex> lockPrint(_screenMutex);
            std::cout << boost::format("main ïîòîê: %1% ñòðîê, %2% áëîêîâ, %3% êîìàíä") % aLines % aBulks % aCommands << std::endl;
        }
        PrintStat("log ïîòîê", _loggerScreen);
        PrintStat("file1 ïîòîê", _loggerFile1);
        PrintStat("file2 ïîòîê", _loggerFile2);
    }
private:
    CmdLogger() = default;
    std::mutex _screenMutex;
    std::unique_ptr<ILogger> _loggerScreen;
    std::unique_ptr<ILogger>   _loggerFile1;
    std::unique_ptr<ILogger>   _loggerFile2;
    std::size_t _counterBulk = 0;
    std::size_t _ñounterCommands = 0;

    void SaveInFile(std::unique_ptr<ILogger>& aFileLogger, const std::string& aStr, const std::size_t aCommandsNum) {
        if (aFileLogger)
            aFileLogger->Output(aStr, aCommandsNum);
    }

    void PrintStat(const std::string aThrName, std::unique_ptr<ILogger>& aLogger) {
        if (!aLogger)
            return;

        const auto stat = aLogger->GetStat();
        std::lock_guard<std::mutex> lockPrint(_screenMutex);
        std::cout << boost::format("%1%: %2% - áëîêîâ, %3% - êîìàíä") % aThrName % stat.Bulks % stat.Commands << std::endl;
    }
};
