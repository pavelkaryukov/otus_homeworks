#pragma once
#include <string> 
#include <iostream>
#include <boost/format.hpp>
#include <fstream>
#include <time.h> 
#include <filesystem>

class CmdLogger final {
public:
    void WriteCmd(const std::string& aStr) {
        SaveInFile(aStr);
        PrintOnTheScreen(aStr);
    }

    void StartBulk() {
        CreateLogFile();
        SaveInFile("bulk:");
        PrintOnTheScreen("bulk:");
    }
    
    void FinishBulk() {
        SaveInFile("\r\n");
        PrintOnTheScreen("\r\n");
        CloseLogFile();
    }
private:
    std::ofstream m_File;
    
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
        for (; bulkTime <= createTime + 100; ++bulkTime){
            std::string filename = "bulk_" + std::to_string(bulkTime) + ".txt";
            if (std::filesystem::exists(filename))
                continue;

            m_File.open(filename);
            if (m_File.is_open())
                return;
        }
        
        throw std::logic_error(boost::str(boost::format("Can't create bulk log file, time from %1% for %2%") % createTime % bulkTime));
    }

    void PrintOnTheScreen(const std::string& aStr) {
        std::cout << boost::format("%1%") % aStr;
    }

};
