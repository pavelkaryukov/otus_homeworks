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
bool mystr::IsCorrectNumber(const char* aStr) 
{
    const auto len = strlen(aStr);
    for (int i = 0; i < len; i++) {
        if (!std::isdigit(aStr[i]))
            return false;
    }
    return true;
}
//-----------------------------------------------------------------------------
std::vector<std::string> mystr::GetTokens(std::string aStr, const std::string& aDelimeters, std::function<bool(const char*)> aIsCorrectNum)
{
    std::vector<std::string> tokens;
    //const std::string kDelimeters = "\r\n\t ";
    char* str = (char*)aStr.c_str(); //Maybe strcpy ?
    char * pch = strtok(str, aDelimeters.c_str());;// strtok(str, delimeters.c_str());
    while (pch) {
        if ((pch != nullptr) && ((aIsCorrectNum == nullptr) || IsCorrectNumber(pch)))
            tokens.push_back(std::string(pch));
        pch = strtok(NULL, aDelimeters.c_str());
    }
    return tokens;
}
//-----------------------------------------------------------------------------
std::vector<std::size_t> mystr::ConvertStrArrayToNumbers(const std::vector<std::string>& aStrings, /*const*/ std::function<bool(std::size_t)> aIsCorrectNum /*= nullptr*/)
{
    auto res = std::vector<std::size_t>();
    for (auto& elem : aStrings) {
        auto digit = std::atoi(elem.c_str());
        if ((aIsCorrectNum == nullptr) || aIsCorrectNum(digit)) {
            res.emplace_back(digit);
        } else {
            return {};//Если число не соответсвует определенному условию - вернуть пустой вектор
        }
    }
    return res;
}

//-----------------------------------------------------------------------------