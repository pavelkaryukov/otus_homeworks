#pragma once
#include <string>
#include <cstring>
#include <vector>
#include <functional>

namespace mystr
{
    std::string Fmt(const char *fmt, ...);
    bool IsCorrectNumber(const char* aStr); //TODO::Вынести
    //std::vector<std::string> GetAllNumbers(std::string aStr, const std::string& aDelimeters);
    std::vector<std::string> GetTokens(std::string aStr, const std::string& aDelimeters, std::function<bool(const char*)> aIsCorrectNum = nullptr);
    std::vector<std::size_t> ConvertStrArrayToNumbers(const std::vector<std::string>& aStrings, std::function<bool(std::size_t)> aIsCorrectNum = nullptr);

}
