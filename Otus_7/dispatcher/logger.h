#pragma once
#include <string> 
#include <iostream> 
//Logger Command -> ������� ������ ����� � ���� ������
class Logger {
public:
    void SaveInLog(const std::string& aStr) {
        int stop1 = 0;
    };
    
    void PrintOnTheScreen(const std::string& aStr) {
        int stop1 = 0;
    }

    void CreateLogFile() {
        CloseLogFile();
    }
    
    void CloseLogFile() {

    }
private:
};
