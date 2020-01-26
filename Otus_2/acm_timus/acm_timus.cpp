#include "acm_timus.h"
#include <vector>
#include <cctype>
#include <iostream>
#include <cmath>
#include <optional>
#include "my_str.h"
//-----------------------------------------------------------------------------
static const std::string kDelimeters = "\r\n\t ";
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
    unk,
    null
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
    if (!mystr::IsCorrectNumber(aStr.c_str()))
        return  { false, kErrorInputData + "�� �����\r\n" };
    auto digit = std::atoi(aStr.c_str());
    if ((digit < 1) || (digit > 2000)) 
        return { false, kErrorInputData + ":����� �� �� ��������� (1..2000)\r\n" };
    auto numberOfUnits = GetLocalizedNumberOfUnits(digit);
    if (!numberOfUnits)
        return { false, kErrorInputData + ":����� �� �� ��������� (1..2000)\r\n" };

    return {true, ConvertToStr(*numberOfUnits)};
}
//-----------------------------------------------------------------------------
std::string acm_timus::InvSqr(std::string aStr)
{
    std::string resStr;
    auto tokens = mystr::GetTokens(aStr, kDelimeters, mystr::IsCorrectNumber);

    for (auto token = tokens.crbegin(); token != tokens.crend(); token++) {
        auto digit = std::atoll(token->c_str());
        auto sqrtRes = sqrt(digit);
        char buffer[256] = {};
        sprintf(buffer, "%.4f\r\n", sqrtRes);
        resStr += std::string(buffer);
    }
    return resStr;
}
//-----------------------------------------------------------------------------
bool IsGrishaCanSolve(const std::size_t aSolvedInFirstHourTasks)
{
    if ((aSolvedInFirstHourTasks > 11) || (aSolvedInFirstHourTasks < 0))
        return false;
    const std::size_t kNumberOfTasks = 12, kRestTime = 4 * 60; // 12 ������� �� 5 �����, 
    const std::size_t restTasks = kNumberOfTasks - aSolvedInFirstHourTasks;
    return  restTasks * 45 <= kRestTime;
}
//-----------------------------------------------------------------------------
std::string acm_timus::GrishaCanSolve(const std::string& aSolvedInFirstHourTasksStr)
{
    if (!mystr::IsCorrectNumber(aSolvedInFirstHourTasksStr.c_str()))
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
std::size_t acm_timus::NecessarySulfideThoriumWeight(std::string aStr)
{
    auto tokens = mystr::GetTokens(aStr, kDelimeters, mystr::IsCorrectNumber);
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
void acm_timus::AcmTimusTaskExecute()
{
    auto task1000 = acm_timus::Sum(5, 1);
    std::string allStr(" 1427  0   \r\n\r\n876652098643267843\r\n5276538\r\n\r\n");
    auto task1001 = acm_timus::InvSqr(allStr);
    auto task1785a = acm_timus::ToLocalizedNumberOfUnits("7");
    auto task1785b = acm_timus::ToLocalizedNumberOfUnits("7.2");
    auto task1785c = acm_timus::ToLocalizedNumberOfUnits("400");
    auto task1785d = acm_timus::ToLocalizedNumberOfUnits("40");
    auto task1785f = acm_timus::ToLocalizedNumberOfUnits("0");
    auto task2012a = acm_timus::GrishaCanSolve("7");
    auto task2012b = acm_timus::GrishaCanSolve("5");
    auto task2012c = acm_timus::GrishaCanSolve("s7");
    auto task2012d = acm_timus::GrishaCanSolve("70");
    auto task1293a = acm_timus::NecessarySulfideThoriumWeight("5 2 3");
    auto task1293b = acm_timus::NecessarySulfideThoriumWeight("5 223 3");
    auto task1293c = acm_timus::NecessarySulfideThoriumWeight("5 2 ");
    //TODO:: ����� � ��������� ������ �� ���������� �����
}




