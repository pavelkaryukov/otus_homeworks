#include "acm_timus.h"
#include <cctype>
#include <iostream>
#include <cmath>
#include <optional>
#include "my_str.h"
#include <algorithm>
//-----------------------------------------------------------------------------
static const std::string kDelimeters = "\r\n\t ";
//-----------------------------------------------------------------------------
enum class NumberOfUnits
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
    unk,
    null
};
//-----------------------------------------------------------------------------
NumberOfUnits GetLocalizedNumberOfUnits(const int aNumber)
{
    auto FromRange = [&aNumber](const int aLeft, const int aRight) -> bool {
        return (aNumber >= aLeft) && (aNumber <= aRight);
    };

    if (FromRange(1   , 4   )) return  NumberOfUnits::few     ;
    if (FromRange(5   , 9   )) return  NumberOfUnits::several ;
    if (FromRange(10  , 19  )) return  NumberOfUnits::pack    ;
    if (FromRange(20  , 49  )) return  NumberOfUnits::lots    ;
    if (FromRange(50  , 99  )) return  NumberOfUnits::horde   ;
    if (FromRange(100 , 249 )) return  NumberOfUnits::throng  ;
    if (FromRange(250 , 499 )) return  NumberOfUnits::swarm   ;
    if (FromRange(500 , 999 )) return  NumberOfUnits::zounds  ;
    if (FromRange(1000, 2000)) return  NumberOfUnits::legion  ;
    return NumberOfUnits::null;
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
static const std::string kErrorInputData = "Некорректные входные данные:";
std::pair<bool, std::string> acm_timus::ToLocalizedNumberOfUnits(const std::string& aStr)
{
    if (!mystr::IsCorrectNumber(aStr.c_str()))
        return  { false, kErrorInputData + "Не число\r\n" };
    auto digit = std::atoi(aStr.c_str());
    if ((digit < 1) || (digit > 2000)) 
        return { false, kErrorInputData + ":Число не из диапозона (1..2000)\r\n" };
    auto numberOfUnits = GetLocalizedNumberOfUnits(digit);
    if (numberOfUnits == NumberOfUnits::null)
        return { false, kErrorInputData + ":Число не из диапозона (1..2000)\r\n" };

    return {true, ConvertToStr(numberOfUnits)};
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
    const std::size_t kNumberOfTasks = 12, kRestTime = 4 * 60; // 12 заданий на 5 часов, 
    const std::size_t restTasks = kNumberOfTasks - aSolvedInFirstHourTasks;
    return  restTasks * 45 <= kRestTime;
}
//-----------------------------------------------------------------------------
std::string acm_timus::GrishaCanSolve(const std::string& aSolvedInFirstHourTasksStr)
{
    if (!mystr::IsCorrectNumber(aSolvedInFirstHourTasksStr.c_str()))
        return kErrorInputData + aSolvedInFirstHourTasksStr + " - Не число\r\n";
    auto numberOfTasks = std::atoi(aSolvedInFirstHourTasksStr.c_str());
    if ((numberOfTasks < 0) || (numberOfTasks > 11)) {
        return kErrorInputData + "Число {" + aSolvedInFirstHourTasksStr + "} < 0 или > 11";
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
        std::cout << kErrorInputData << "Не достаточное количество аргументов" << std::endl;
        return 0;
    }
    auto numberOfPannels = std::atoi(tokens[0].c_str()), sizeA = std::atoi(tokens[1].c_str()), sizeB = std::atoi(tokens[2].c_str());

    auto FromRange = [leftBorder = 1, rightBorder = 100](const int aNumber) -> bool {
        return (aNumber >= leftBorder) && (aNumber <= rightBorder);
    };

    if (!FromRange(numberOfPannels) || !FromRange(sizeA) || !FromRange(sizeB)) {
        std::cout << kErrorInputData << numberOfPannels << ", " << sizeA << ", " << sizeB << " вне диапазона  1..100" << std::endl;
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
    //TODO:: Вывод в командную строку на английском языке
}
//-----------------------------------------------------------------------------
void acm_timus::TwoGangsta(const std::string& aStr)
{
    auto tokens = mystr::GetTokens(aStr, " \r\n\t", mystr::IsCorrectNumber);
    if (tokens.size() < 2)
        return;
    const std::size_t maxNumberOfTin = 10;
    auto numbers = mystr::ConvertStrArrayToNumbers(tokens, [&maxNumberOfTin](const std::size_t aNum)->bool { return aNum <= maxNumberOfTin; });
    if ((numbers.size() < 2) || (numbers[0] == 0) || (numbers[1] == 0))
        return;

    const std::size_t  numberOfTin = numbers[0] + numbers[1] - 1;
    if (numberOfTin > maxNumberOfTin)
        return;

    std::cout << numberOfTin - numbers[0] << " " << numberOfTin - numbers[1] << std::endl;
}
//-----------------------------------------------------------------------------
bool acm_timus::CanOpen(const std::pair<std::string, std::string>& aLocksStr)
{
    const std::size_t kLockStrSize = 4;
    if ((aLocksStr.first.size() != kLockStrSize) || (aLocksStr.second.size() != kLockStrSize))
        return false;
    if (!mystr::IsCorrectNumber(aLocksStr.first.c_str()) || !mystr::IsCorrectNumber(aLocksStr.second.c_str()))
        return false;
    std::pair<std::size_t, std::size_t> locks = { std::stoi(aLocksStr.first),  std::stoi(aLocksStr.second) };    
    // поидеи - в первый день будут только четные числа, во второй только не четные
    return (locks.first % 2 == 0) || (locks.second % 2 == 1);
}

//-----------------------------------------------------------------------------
bool acm_timus::BerryWeight(const std::vector<std::string>& aWeighingResStr, std::pair<std::size_t, std::size_t>& aBerrysWeight)
{
    if (aWeighingResStr.size() != 3)
        return false;
    std::vector<std::pair<std::size_t, std::size_t>> aWeighingRes;
    for (const auto& str : aWeighingResStr) {
        auto tokens = mystr::GetTokens(str, " \r\n\t", mystr::IsCorrectNumber);
        if (tokens.size() != 2)
            return false;
        auto weights = mystr::ConvertStrArrayToNumbers(tokens, [](std::size_t aWeight)->bool { return aWeight <= 10000; });
        if (weights.size() != 2)
            return false;
        aWeighingRes.push_back({ weights[0], weights[1] });
    }
    if (aWeighingRes.size() != 3) 
        return false;
    bool correctWeights1 = (aWeighingRes[2].first <= aWeighingRes[0].first) && (aWeighingRes[0].first <= aWeighingRes[1].first);
    bool correctWeights2 = (aWeighingRes[2].second >= aWeighingRes[0].second) && (aWeighingRes[0].second >= aWeighingRes[1].second);
    if (!correctWeights1 || !correctWeights2)
        return false;

    std::size_t berrys1 = aWeighingRes[0].first - aWeighingRes[2].first;
    std::size_t berrys2 = aWeighingRes[0].second - aWeighingRes[1].second;
    
    std::size_t basket1 = aWeighingRes[2].first;
    std::size_t basket2 = aWeighingRes[1].second;
    bool correctWeights3 = basket1 + berrys2 + berrys1 == aWeighingRes[1].first;
    bool correctWeights4 = basket2 + berrys2 + berrys1 == aWeighingRes[2].second;
    if (!correctWeights3 || !correctWeights4)
        return false;
    //std::size_t basket1 = 
    aBerrysWeight = { berrys1 , berrys2 };
    return true;
}
//-----------------------------------------------------------------------------
std::pair<bool, std::size_t> acm_timus::NecessarySeconds(std::string& aStr)
{
    const std::pair<bool, std::size_t> kNegativeRes{ false, 0 };
    auto tokens = mystr::GetTokens(aStr, " \r\n\t", mystr::IsCorrectNumber);
    if (tokens.size() != 2)
        return kNegativeRes;
    auto numbers = mystr::ConvertStrArrayToNumbers(tokens, [](std::size_t aNum)->bool { return aNum <= 40000; });
    if (numbers.size() != 2)
        return kNegativeRes;

    return { true, numbers[0] * (numbers[1] + 1) };
}
//-----------------------------------------------------------------------------
std::pair<bool, std::size_t> acm_timus::RestOfCar(std::vector<std::string> aStrs)
{
    const std::pair<bool, std::size_t> kNegativeRes{ false, 0 };
    if (aStrs.size() != 2)
        return kNegativeRes;
    
    const std::string kDelimeters = " \r\n\t";
    auto bound = [](std::size_t aNum)->bool { return aNum <= 100; };
    auto bandwidthAndDuration = mystr::ConvertStrArrayToNumbers(mystr::GetTokens(aStrs[0], kDelimeters), bound);
    if (bandwidthAndDuration.size() != 2)
        return kNegativeRes;                                          
    
    auto bandwidth = bandwidthAndDuration[0], duration = bandwidthAndDuration[1];
    auto cars = mystr::ConvertStrArrayToNumbers(mystr::GetTokens(aStrs[1], kDelimeters), bound);
    if (cars.size() != duration)
        return kNegativeRes;

    std::size_t restOfCars = 0;
    for (const auto& car : cars) {
        restOfCars += car;
        if (restOfCars >= bandwidth)
            restOfCars -= bandwidth;
        else
            restOfCars = 0;
    }
    return {true, restOfCars};
}
//-----------------------------------------------------------------------------
std::size_t acm_timus::SteakCookingTime(std::string aStr)
{
    auto bound = [](std::size_t aNum)->bool { return (aNum >= 1) && (aNum <= 1000); };
    const std::string kDelimeters = " \r\n\t";
    auto conditions = mystr::ConvertStrArrayToNumbers(mystr::GetTokens(aStr, kDelimeters, nullptr), bound);
    if (conditions.size() != 2)
        return 0;
    const std::size_t number = conditions[0], capacity = conditions[1];
    const std::size_t minSteakCookingTime = 2;
    if (number <= capacity)
        return minSteakCookingTime;
    return  ceil((number * 2) / (capacity + .0));
}
//-----------------------------------------------------------------------------
std::string acm_timus::MinPossibleNumber(std::size_t a, std::size_t b, std::size_t c)
{
    const size_t kMaxNum = 100;
    if ((a > kMaxNum) || (b > kMaxNum) || (c > kMaxNum))
        return "";
    std::vector<std::size_t> numbers = { a,b,c };
std:size_t minNum = 0;
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
        if ((*iter <= a) && (*iter <= b) && (*iter <= c)) {
            minNum = *iter;
            numbers.erase(iter);
            break;
        }
    }
    int res1 = minNum - numbers[0] * numbers[1];
    int res2 = minNum - numbers[0] - numbers[1];
    return std::to_string(std::min(res1, res2));
}
//-----------------------------------------------------------------------------
bool IsCorrectChessNumber(const char* aStr)
{
    const auto len = strlen(aStr);
    if (len <= 1 || len > 2)
        return false;

    if ((!std::isalpha(aStr[0])) || (!std::islower(aStr[0])) || (aStr[0] > 'h'))
        return false;
    for (int i = 1; i < len; i++) {
        if (!std::isdigit(aStr[i]) || (aStr[i] == '0') || (aStr[i] > '8'))
            return false;
    }
    return true;
}
//-----------------------------------------------------------------------------
bool IsPossibleMovement(const char aPosX, const char aPosY)
{
    if (aPosX <'a' || aPosX > 'h')
        return false;
    if (aPosY <'1' || aPosY > '8')
        return false;
    return true;
}
//-----------------------------------------------------------------------------
std::size_t PossibleMovementNumber(const char aPosX, const char aPosY)
{
    std::size_t movementNumber = 0;

    movementNumber += IsPossibleMovement(aPosX + 2, aPosY + 1) ? 1 : 0;
    movementNumber += IsPossibleMovement(aPosX + 2, aPosY - 1) ? 1 : 0;
    movementNumber += IsPossibleMovement(aPosX - 2, aPosY + 1) ? 1 : 0;
    movementNumber += IsPossibleMovement(aPosX - 2, aPosY - 1) ? 1 : 0;


    movementNumber += IsPossibleMovement(aPosX + 1, aPosY + 2) ? 1 : 0;
    movementNumber += IsPossibleMovement(aPosX + 1, aPosY - 2) ? 1 : 0;
    movementNumber += IsPossibleMovement(aPosX - 1, aPosY + 2) ? 1 : 0;
    movementNumber += IsPossibleMovement(aPosX - 1, aPosY - 2) ? 1 : 0;

    return movementNumber;
}
//-----------------------------------------------------------------------------
std::vector<std::size_t> acm_timus::PossibleChessHorseMovment(const std::vector<std::string>& aStrs)
{
    std::vector<std::size_t> res;
    for (auto& str : aStrs){
        auto tokens = mystr::GetTokens(str, kDelimeters, IsCorrectChessNumber);
        for (const auto& token : tokens){
            if (token.size() != 2)
                continue;
            res.emplace_back(PossibleMovementNumber(token[0], token[1]));
        }
    }
    return std::move(res);
}
//-----------------------------------------------------------------------------
std::string acm_timus::DinnerCost(const std::vector<std::string>& aStrs)
{
    std::size_t clientsNumber = 2;
    for (const auto& invite : aStrs) {
        if ((invite.size() < 1) /*|| (invite.size() > 20)*/)
            continue;

        auto names = mystr::GetTokens(invite, " +\r\n\t", nullptr);
        if ((names.size() > 1) && (names[1] != "one"))
            continue;
        clientsNumber += names.size();
    }

    clientsNumber = clientsNumber == 13 ? clientsNumber + 1 : clientsNumber;
    const std::size_t kClienCost = 100;
    auto dinnerCost = clientsNumber * kClienCost;
    return std::to_string(dinnerCost);
}
//-----------------------------------------------------------------------------
std::string acm_timus::CommandNumbersCount(std::vector<std::pair<std::size_t, std::string>> aCommandData)
{
    std::map<std::size_t, std::size_t> teamNumbersMap;
    for (const auto& playerData : aCommandData) {
        auto numbers = mystr::ConvertStrArrayToNumbers(
            mystr::GetTokens(playerData.second, " +\r\n\t", mystr::IsCorrectNumber),
            [](std::size_t aNum)->bool { return aNum <= 1'000'000'000; }
        );
        if ((numbers.size() != playerData.first))
            continue;//Как бы не ретерн
        for (const auto number : numbers) {
            teamNumbersMap[number]++;
        }
    }
    std::size_t teamNumbersCount = 0;
    for (const auto& numberCost : teamNumbersMap) {
        teamNumbersCount += (numberCost.second == aCommandData.size()) ? 1 : 0;
    }
    return std::to_string(teamNumbersCount);
}
//-----------------------------------------------------------------------------