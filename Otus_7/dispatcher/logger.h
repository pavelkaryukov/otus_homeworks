#pragma once
#include <string> 
#include <iostream>
#include <boost/format.hpp>
#include <fstream>
#include <time.h> 
#include <filesystem>
class CmdLoggerFile {
public:
    void SaveInFile(const std::string& aStr) {
        if (!m_File.is_open())
            return;
        m_File << aStr;
    };

    void CloseLogFile() {
        if (m_File.is_open())
            m_File.close();
    }

    void CreateLogFile() {
        CloseLogFile();
        auto createTime = time(nullptr);
        auto bulkTime = createTime;
        for (; bulkTime <= createTime + 100; ++bulkTime) {
            std::string filename = "bulk_" + std::to_string(bulkTime) + ".txt";
            if (std::filesystem::exists(filename))
                continue;

            m_File.open(filename);
            if (m_File.is_open())
                return;
        }

        throw std::logic_error(boost::str(boost::format("Can't create bulk log file, time from %1% for %2%") % createTime % bulkTime));
    }
private:
    std::ofstream m_File;
};

class CmdLoggerStream {
public:
    CmdLoggerStream(std::ostream& aStream) : m_Stream(aStream) {}

    void PrintOnTheScreen(const std::string& aStr) {
        m_Stream << boost::format("%1%") % aStr;
    }
private:
    std::ostream& m_Stream = std::cout;
};

class CmdLogger {
public:
    CmdLogger(std::ostream& aStream) : m_LoggerStream({ aStream }) {}

    void WriteCmd(const std::string& aStr) {
        m_LoggerFile.SaveInFile(aStr);
        m_LoggerStream.PrintOnTheScreen(aStr);
    }

    void StartBulk() {
        m_LoggerFile.CreateLogFile();
        m_LoggerFile.SaveInFile("bulk:");
        m_LoggerStream.PrintOnTheScreen("bulk:");
    }
    
    void FinishBulk() {
        m_LoggerFile.SaveInFile("\r\n");
        m_LoggerFile.CloseLogFile();
        m_LoggerStream.PrintOnTheScreen("\r\n");
    }
private:
    CmdLoggerStream m_LoggerStream;
    CmdLoggerFile   m_LoggerFile;
};
