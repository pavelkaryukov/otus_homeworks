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

    void Save(const std::string aStr) {
        ++_counter;
        if (_loggerScreen)
            _loggerScreen->Output(aStr);

        SaveInFile((_counter % 2 == 1) ? _loggerFile1 : _loggerFile2, aStr);
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
private:
    CmdLogger() = default;
    std::mutex _screenMutex;
    std::unique_ptr<LoggerScreen> _loggerScreen;
    std::unique_ptr<LoggerFile>   _loggerFile1;
    std::unique_ptr<LoggerFile>   _loggerFile2;
    std::size_t _counter = 0;

    void SaveInFile(std::unique_ptr<LoggerFile>& aFileLogger, const std::string& aStr) {
        if (aFileLogger)
            aFileLogger->Output(aStr);
    }
};
