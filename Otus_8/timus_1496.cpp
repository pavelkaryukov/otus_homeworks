#include <cctype>
#include <map>
#include <string>
#include <iostream>
#include <cstring>

namespace mystr {
    bool IsCorrectNumber(const char* aStr) {
        const auto len = strlen(aStr);
        for (auto i = 0U; i < len; i++) {
            if (!std::isdigit(aStr[i]))
                return false;
        }
        return true;
    }

    bool IsCorrectNumber(const std::string& aStr) {
        return IsCorrectNumber(aStr.c_str());
    }
}

bool IsCorrectTeamName(const std::string& aStr) {
    if (aStr.empty() || aStr.size() > 30)
        return false;
    for (auto& ch : aStr) {
        if (!std::islower(ch) && !std::isdigit(ch))
            return false;
    }
    return true;
}


bool SubmitsNumber(const std::string& aStr, std::size_t& aSize) {
    if (!mystr::IsCorrectNumber(aStr))
        return false;
    aSize = std::atoi(aStr.c_str());
    if (aSize < 1 || aSize > 1000)
        return false;
    return true;
}

int main() {
    std::string str;
    std::size_t size = 0;
    std::size_t counter = 0;
    std::getline(std::cin, str);
    if (!SubmitsNumber(str, size))
        return 0;

    std::map<std::string, std::size_t> teamSubmits;
    while (((counter++) < size) && std::getline(std::cin, str)) {
        //Input Dictionary case
        if (!IsCorrectTeamName(str))
            return 0;
        teamSubmits[str] += 1;
    }

    for (const auto& submit : teamSubmits) {
        const auto& team = submit.first;
        if (submit.second > 1)
            std::cout << team << std::endl;
    }

    return 0;
}