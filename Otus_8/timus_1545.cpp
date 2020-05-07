#include <cctype>
#include <map>
#include <set>
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

    bool IsLowerAlpha(const std::string& aStr) {
        for (auto& ch : aStr) {
            if (!std::islower(ch))
                return false;
        }
        return true;
    }
}

bool InputDictSize(const std::string& aStr, std::size_t& aSize) {
    if (!mystr::IsCorrectNumber(aStr))
        return false;
    aSize = std::atoi(aStr.c_str());
    if (aSize < 1 || aSize > 1000)
        return false;
    return true;
}


namespace {
    using dict_t = std::map<char, std::set<std::string>>;
}

int main() {
    std::string str;
    std::size_t size = 0;
    std::size_t counter = 0;
    std::getline(std::cin, str);
    if (!InputDictSize(str, size))
        return 0;

    dict_t dictionary;
    while (((counter++) < size) && std::getline(std::cin, str)) {
        //Input Dictionary case
        if (str.size() != 2 || !mystr::IsLowerAlpha(str))
            return 0;
        dictionary[str[0]].insert(str);
    }

    while (std::getline(std::cin, str)) {
        if (str.size() != 1 || !mystr::IsLowerAlpha(str))
            continue;
        const auto& ch = str[0];
        auto iter = dictionary.find(ch);
        if (iter == dictionary.end())
            continue;
        for (const auto& elem : iter->second) {
            std::cout << elem << std::endl;
        }
    }
    return 0;
}