#pragma once       
#include "concurrent/concurrent_deque.h"
#include "logger/logger_screen.h" 
#include <string> 
#include <boost/format.hpp>
#include <fstream>
#include <time.h> 
#include <filesystem>

void SaveLogInFile(std::string aStr) {
    auto createTime = time(nullptr);
    auto bulkTime = createTime;
    for (; bulkTime <= createTime + 100; ++bulkTime) {
        std::string filename = "bulk_" + std::to_string(bulkTime) + ".txt";
        if (std::filesystem::exists(filename))
            continue;

        std::ofstream file(filename);
        if (file.is_open()) {
            file << aStr;
        }
    }
}

void PrintLog(std::string aStr, std::ostream& aStream) {
    aStream << aStr << std::endl;;
}


class CmdLogger {
public:
    CmdLogger(std::ostream& aStream) {
        _loggerScreen = std::make_unique<LoggerScreen>(aStream, _screenMutex);
    }

    void Save(const std::string aStr) {
        if (!_loggerScreen)
            return;
        _loggerScreen->Output(aStr);
    }
private:
    CmdLogger() = default;
    std::mutex _screenMutex;
    std::unique_ptr<LoggerScreen> _loggerScreen;
};
