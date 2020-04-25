#pragma once
#include <string> 
#include <iostream>
#include <boost/format.hpp>
//Logger Command -> команды должны иметь к нему доступ
class Logger {
public:
    void WriteCmd(const std::string& aStr) {
        SaveInFile(aStr);
        PrintOnTheScreen(aStr);
    }

    void StartBulk() {
        CloseLogFile();
        CreateLogFile();
        SaveInFile(" bulk:");
        PrintOnTheScreen(" bulk:");
    }
    
    void FinishBulk() {
        SaveInFile("\r\n");
        PrintOnTheScreen("\r\n");
        CloseLogFile();
    }
private:
    void SaveInFile(const std::string& aStr) {
        int stop1 = 0;
    };


    void CloseLogFile() {}

    void CreateLogFile() {}

    void PrintOnTheScreen(const std::string& aStr) {
        std::cout << boost::format("%1%") % aStr;
    }

};
