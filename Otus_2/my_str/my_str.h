#pragma once
#include <string>
#include <cstring>
#include <vector>
namespace mystr
{
    std::string Fmt(const char *fmt, ...);
    bool IsCorrectNumber(const char* aStr); //TODO::�������
    std::vector<std::string> GetAllNumbers(std::string aStr);//TODO::�������
}
