#include "acm_timus.h"
#include <vector>
#include <cctype>
#include <optional>
#include <iostream>

//-----------------------------------------------------------------------------
bool IsCorrectNumber(const char* aStr)
{
    for (int i = 0; i < strlen(aStr); i++) {        
        if (!std::isdigit(aStr[i]))
            return false;
    }
    return true;
}
//-----------------------------------------------------------------------------
std::vector<std::string> GetAllNumbers(std::string aStr)
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
enum class NumberOfUnits
{
    few,        //�� 1   �� 4	  ��������� few
    several,    //�� 5   �� 9	  ������� several
    pack,       //�� 10  �� 19	  ����� pack
    lots,       //�� 20  �� 49	  ����� lots
    horde,      //�� 50  �� 99	  ���� horde
    throng,     //�� 100 �� 249	  ��������� throng
    swarm,      //�� 250 �� 499	  ������� swarm
    zounds,     //�� 500 �� 999	  ������� zounds
    legion,     //�� 1000	      ������ legion
    unk
};
//-----------------------------------------------------------------------------
std::optional<NumberOfUnits> GetLocalizedNumberOfUnits(const int aNumber)
{
    auto FromRange = [&aNumber](const int aLeft, const int aRight) -> bool {
        return (aNumber >= aLeft) && (aNumber <= aRight);
    };

    if (FromRange(1   , 4   )) return { NumberOfUnits::few     };
    if (FromRange(5   , 9   )) return { NumberOfUnits::several };
    if (FromRange(10  , 19  )) return { NumberOfUnits::pack    };
    if (FromRange(20  , 49  )) return { NumberOfUnits::lots    };
    if (FromRange(50  , 99  )) return { NumberOfUnits::horde   };
    if (FromRange(100 , 249 )) return { NumberOfUnits::throng  };
    if (FromRange(250 , 499 )) return { NumberOfUnits::swarm   };
    if (FromRange(500 , 999 )) return { NumberOfUnits::zounds  };
    if (FromRange(1000, 2000)) return { NumberOfUnits::swarm   };
    return std::nullopt;
}
//-----------------------------------------------------------------------------
std::string ConvertToStr(const NumberOfUnits aLocalizedNum)
{
    switch (aLocalizedNum) {
    default:    return "unknown";
    case NumberOfUnits::few    :     return "few"    ;
    case NumberOfUnits::several:     return "several";
    case NumberOfUnits::pack   :     return "pack"   ;
    case NumberOfUnits::lots   :     return "lots"   ;
    case NumberOfUnits::horde  :     return "horde"  ;
    case NumberOfUnits::throng :     return "throng" ;
    case NumberOfUnits::swarm  :     return "swarm"  ;
    case NumberOfUnits::zounds :     return "zounds" ;
    case NumberOfUnits::legion :     return "legion" ;
    case NumberOfUnits::unk    :     return "unk"    ;
    }
}
//-----------------------------------------------------------------------------
static const std::string kErrorInputData = "������������ ������� ������:";
std::pair<bool, std::string> acm_timus::ToLocalizedNumberOfUnits(const std::string& aStr)
{
    if (!IsCorrectNumber(aStr.c_str()))
        return  { false, kErrorInputData + "�� �����\r\n" };
    auto digit = std::atoi(aStr.c_str());
    if ((digit < 1) || (digit > 2000)) 
        return { false, kErrorInputData + ":����� �� �� ��������� (1..2000)\r\n" };
    auto localizedNum = GetLocalizedNumberOfUnits(digit);
    if (!localizedNum)
        return { false, kErrorInputData + ":����� �� �� ��������� (1..2000)\r\n" };

    return {true, ConvertToStr(*localizedNum)};
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
bool IsGrishaCanSolve(const size_t aSolvedInFirstHourTasks)
{
    if ((aSolvedInFirstHourTasks > 11) || (aSolvedInFirstHourTasks < 0))
        return false;
    const size_t kNumberOfTasks = 12, kRestTime = 4 * 60; // 12 ������� �� 5 �����, 
    const size_t restTasks = kNumberOfTasks - aSolvedInFirstHourTasks;
    return  restTasks * 45 <= kRestTime;
}
//-----------------------------------------------------------------------------
std::string acm_timus::GrishaCanSolve(const std::string& aSolvedInFirstHourTasksStr)
{
    if (!IsCorrectNumber(aSolvedInFirstHourTasksStr.c_str()))
        return kErrorInputData + aSolvedInFirstHourTasksStr + " - �� �����\r\n";
    auto numberOfTasks = std::atoi(aSolvedInFirstHourTasksStr.c_str());
    if ((numberOfTasks < 0) || (numberOfTasks > 11)) {
        return kErrorInputData + "����� {" + aSolvedInFirstHourTasksStr + "} < 0 ��� > 11";
    }
    return IsGrishaCanSolve(numberOfTasks) ? "YES" : "NO";
}
//-----------------------------------------------------------------------------
bool IsNumberFromRange(const int aNumber, const int aLeft, const int aRight)
{
    return (aNumber >= 1) && (aNumber <= 100);
}
//-----------------------------------------------------------------------------
size_t acm_timus::NecessarySulfideThoriumWeight(std::string aStr)
{
    auto tokens = GetAllNumbers(aStr);
    if (tokens.size() < 3) {
        std::cout << kErrorInputData << "�� ����������� ���������� ����������" << std::endl;
        return 0;
    }
    auto numberOfPannels = std::atoi(tokens[0].c_str()), sizeA = std::atoi(tokens[1].c_str()), sizeB = std::atoi(tokens[2].c_str());

    auto FromRange = [leftBorder = 1, rightBorder = 100](const int aNumber) -> bool {
        return (aNumber >= leftBorder) && (aNumber <= rightBorder);
    };

    if (!FromRange(numberOfPannels) || !FromRange(sizeA) || !FromRange(sizeB)) {
        std::cout << kErrorInputData << numberOfPannels << ", " << sizeA << ", " << sizeB << " ��� ���������  1..100" << std::endl;
        return 0;
    }
    return 2 * numberOfPannels * sizeA * sizeB;
}
//-----------------------------------------------------------------------------




