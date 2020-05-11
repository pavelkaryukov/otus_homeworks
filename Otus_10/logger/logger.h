#pragma once       
#include "logger/logger_screen.h"
#include "logger/logger_file.h"
#include <string> 

class CmdLogger {
public:
    CmdLogger(std::ostream& aStream) {
        m_LoggerScreen = std::make_unique<LoggerScreen>(aStream, m_ScreenMutex);
        m_LoggerFile1 = std::make_unique<LoggerFile>();
        m_LoggerFile2 = std::make_unique<LoggerFile>();
    }

    void Save(const std::string aStr, const std::size_t aCommandsNum) {
        ++m_CounterBulk;
        m_CounterCommands += aCommandsNum;
        if (m_LoggerScreen)
            m_LoggerScreen->Output(aStr, aCommandsNum);

        SaveInFile((m_CounterBulk % 2 == 1) ? m_LoggerFile1 : m_LoggerFile2, aStr, aCommandsNum);
    }

    void Exit() {
        if (m_LoggerScreen)
            m_LoggerScreen->Exit();
        
        if (m_LoggerFile1)
            m_LoggerFile1->Exit();

        if (m_LoggerFile2)
            m_LoggerFile2->Exit();
    }

    ~CmdLogger() {}

    void PrintStat(const std::size_t aLines, const std::size_t aBulks, const std::size_t aCommands) {
        {
            std::lock_guard<std::mutex> lockPrint(m_ScreenMutex);
            std::cout << boost::format("main поток: %1% строк, %2% блоков, %3% команд") % aLines % aBulks % aCommands << std::endl;
        }
        PrintStat("log поток", m_LoggerScreen);
        PrintStat("file1 поток", m_LoggerFile1);
        PrintStat("file2 поток", m_LoggerFile2);
    }
private:
    CmdLogger() = default;
    std::mutex m_ScreenMutex;
    std::unique_ptr<ILogger>   m_LoggerScreen;
    std::unique_ptr<ILogger>   m_LoggerFile1;
    std::unique_ptr<ILogger>   m_LoggerFile2;
    std::size_t m_CounterBulk = 0;
    std::size_t m_CounterCommands = 0;

    void SaveInFile(std::unique_ptr<ILogger>& aFileLogger, const std::string& aStr, const std::size_t aCommandsNum) {
        if (aFileLogger)
            aFileLogger->Output(aStr, aCommandsNum);
    }

    void PrintStat(const std::string aThrName, std::unique_ptr<ILogger>& aLogger) {
        if (!aLogger)
            return;

        const auto stat = aLogger->GetStat();
        std::lock_guard<std::mutex> lockPrint(m_ScreenMutex);
        std::cout << boost::format("%1%: %2% - блоков, %3% - команд") % aThrName % stat.Bulks % stat.Commands << std::endl;
    }
};
