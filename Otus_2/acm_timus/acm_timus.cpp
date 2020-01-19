#include "acm_timus.h"
#include <vector>
#include <cctype>
#include <optional>
//-----------------------------------------------------------------------------
bool IsCorrectNumber(const char* aToken)
{
    for (int i = 0; i < strlen(aToken); i++) {        
        if (!std::isdigit(aToken[i]))
            return false;
    }
    return true;
}
//-----------------------------------------------------------------------------
std::vector<std::string> GetAllNumbers(std::string aStr)
{
    std::vector<std::string> tokens;
    const std::string delimeters = "\r\n\t ";
    char* str = (char*)aStr.c_str(); //Maybe strcpy ?
    char * pch = strtok(str, delimeters.c_str());;// strtok(str, delimeters.c_str());
    while (pch) {
        if ((pch != nullptr) && IsCorrectNumber(pch))
            tokens.push_back(std::string(pch));
        pch = strtok(NULL, delimeters.c_str());
    }
    return tokens;
}
//-----------------------------------------------------------------------------
enum class LocalizedNumber
{
    few,        //от 1   до 4	  несколько few
    several,    //от 5   до 9	  немного several
    pack,       //от 10  до 19	  отряд pack
    lots,       //от 20  до 49	  толпа lots
    horde,      //от 50  до 99	  орда horde
    throng,     //от 100 до 249	  множество throng
    swarm,      //от 250 до 499	  сонмище swarm
    zounds,     //от 500 до 999	  полчище zounds
    legion,     //от 1000	      легион legion
    unk
};
//-----------------------------------------------------------------------------
using LocalizedResult = std::optional<LocalizedNumber>;
LocalizedResult GetLocalizedNumber(const int aNumber)
{
    auto FromRange = [&aNumber](const int aLeft, const int aRight) -> bool {
        return (aNumber >= aLeft) && (aNumber <= aRight);
    };

    if (FromRange(1   , 4   )) return { LocalizedNumber::few     };
    if (FromRange(5   , 9   )) return { LocalizedNumber::several };
    if (FromRange(10  , 19  )) return { LocalizedNumber::pack    };
    if (FromRange(20  , 49  )) return { LocalizedNumber::lots    };
    if (FromRange(50  , 99  )) return { LocalizedNumber::horde   };
    if (FromRange(100 , 249 )) return { LocalizedNumber::throng  };
    if (FromRange(250 , 499 )) return { LocalizedNumber::swarm   };
    if (FromRange(500 , 999 )) return { LocalizedNumber::zounds  };
    if (FromRange(1000, 2000)) return { LocalizedNumber::swarm   };
    return std::nullopt;
}
//-----------------------------------------------------------------------------
std::string ConvertToStr(const LocalizedNumber aLocalizedNum)
{
    switch (aLocalizedNum) {
    default:    return "unknown";
    case LocalizedNumber::few    :     return "few"    ;
    case LocalizedNumber::several:     return "several";
    case LocalizedNumber::pack   :     return "pack"   ;
    case LocalizedNumber::lots   :     return "lots"   ;
    case LocalizedNumber::horde  :     return "horde"  ;
    case LocalizedNumber::throng :     return "throng" ;
    case LocalizedNumber::swarm  :     return "swarm"  ;
    case LocalizedNumber::zounds :     return "zounds" ;
    case LocalizedNumber::legion :     return "legion" ;
    case LocalizedNumber::unk    :     return "unk"    ;
    }
}
//-----------------------------------------------------------------------------
static const std::string kErrorInputData = "Некорректные входные данные:";
std::string acm_timus::ToLocalizedStr(const std::string& aStr)
{
    if (!IsCorrectNumber(aStr.c_str()))
        return  kErrorInputData + "Не число\r\n";
    auto digit = std::atoi(aStr.c_str());
    if ((digit < 1) || (digit > 2000)) 
        return kErrorInputData + ":Число не из диапозона (1..2000)\r\n";
    auto localizedNum = GetLocalizedNumber(digit);
    if (!localizedNum)
        return kErrorInputData + ":Число не из диапозона (1..2000)\r\n";

    return ConvertToStr(*localizedNum);
}
//-----------------------------------------------------------------------------
std::string acm_timus::InvSqr(std::string aStr)
{
    std::string resStr;
    auto tokens = GetAllNumbers(aStr);
    for (auto token = tokens.crbegin(); token != tokens.crend(); token++) {
        auto digit = std::atoll(token->c_str());
        auto sqrtRes = sqrtl(digit);
        char buffer[256] = {};
        sprintf(buffer, "%.4f\r\n", sqrtRes);
        resStr += std::string(buffer);
    }
    return resStr;
}
//-----------------------------------------------------------------------------

