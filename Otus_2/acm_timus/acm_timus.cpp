#include "acm_timus.h"
#include <vector>
#include <cctype>
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
    legion      //от 1000	      легион legion
};
//-----------------------------------------------------------------------------
static const std::string kErrorInputData = "Некорректные входные данные:";
std::string acm_timus::ToLocalizedStr(const std::string& aStr)
{
    if (!IsCorrectNumber(aStr.c_str()))
        return  kErrorInputData + "Не число\r\n";
    auto digit = std::atoi(aStr.c_str());
    if ((digit < 1) || (digit > 2000)) 
        return kErrorInputData + ":Число не из диапозона (1..2000)\r\n";




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
    return "";
}
//-----------------------------------------------------------------------------

