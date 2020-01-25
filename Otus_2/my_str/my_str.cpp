#include "my_str.h"

#include <cctype>
#include <iostream>
#include <stdarg.h>
//-----------------------------------------------------------------------------
std::string mystr::Fmt(const char *fmt, ...) //TODO:: загнать в либу
{
    va_list args;
    va_start(args, fmt);
    std::vector<char> v(1024);
    while (true) {
        va_list args2;
        va_copy(args2, args);
        int res = vsnprintf(v.data(), v.size(), fmt, args2);
        if ((res >= 0) && (res < static_cast<int>(v.size()))) {
            va_end(args);
            va_end(args2);
            return std::string(v.data());
        }
        size_t size;
        if (res < 0)
            size = v.size() * 2;
        else
            size = static_cast<size_t>(res) + 1;
        v.clear();
        v.resize(size);
        va_end(args2);
    }
}
//-----------------------------------------------------------------------------
bool mystr::IsCorrectNumber(const char* aStr) //TODO::Вынести
{
    const auto len = strlen(aStr);
    for (int i = 0; i < len; i++) {
        if (!std::isdigit(aStr[i]))
            return false;
    }
    return true;
}
//-----------------------------------------------------------------------------
std::vector<std::string> mystr::GetAllNumbers(std::string aStr)//TODO::Вынести
{
    std::vector<std::string> tokens;
    const std::string kDelimeters = "\r\n\t ";
    char* str = (char*)aStr.c_str(); //Maybe strcpy ?
    char * pch = strtok(str, kDelimeters.c_str());;// strtok(str, delimeters.c_str());
    while (pch) {
        if ((pch != nullptr) && IsCorrectNumber(pch))
            tokens.push_back(std::string(pch));
        pch = strtok(NULL, kDelimeters.c_str());
    }
    return tokens;
}
//-----------------------------------------------------------------------------