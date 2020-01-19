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
    few,        //�� 1   �� 4	  ��������� few
    several,    //�� 5   �� 9	  ������� several
    pack,       //�� 10  �� 19	  ����� pack
    lots,       //�� 20  �� 49	  ����� lots
    horde,      //�� 50  �� 99	  ���� horde
    throng,     //�� 100 �� 249	  ��������� throng
    swarm,      //�� 250 �� 499	  ������� swarm
    zounds,     //�� 500 �� 999	  ������� zounds
    legion      //�� 1000	      ������ legion
};
//-----------------------------------------------------------------------------
static const std::string kErrorInputData = "������������ ������� ������:";
std::string acm_timus::ToLocalizedStr(const std::string& aStr)
{
    if (!IsCorrectNumber(aStr.c_str()))
        return  kErrorInputData + "�� �����\r\n";
    auto digit = std::atoi(aStr.c_str());
    if ((digit < 1) || (digit > 2000)) 
        return kErrorInputData + ":����� �� �� ��������� (1..2000)\r\n";




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

