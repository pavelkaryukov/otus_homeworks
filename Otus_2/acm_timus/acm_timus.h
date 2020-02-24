#pragma once
#include <string>
#include <cstring>
#include <vector>
namespace acm_timus
{
    //-----------------------------------------------------------------------------
    void TwoGangsta(const std::string& aStr);//Task 1409
    //-----------------------------------------------------------------------------
    std::size_t NecessarySulfideThoriumWeight(std::string aStr);//Task 1293
    //-----------------------------------------------------------------------------
    std::string GrishaCanSolve(const std::string& aSolvedInFirstHourTasksStr);  //Task 2012
    //-----------------------------------------------------------------------------
    std::pair<bool, std::string> ToLocalizedNumberOfUnits(const std::string& aStr); //Task 1785
    //-----------------------------------------------------------------------------
    std::string InvSqr(std::string Str);//Task 1001
    //-----------------------------------------------------------------------------
    template<typename T>
    T Sum(T a, T b) // Task 1000
    {
        return a + b;
    }
    //-----------------------------------------------------------------------------
    void AcmTimusTaskExecute();
    //-----------------------------------------------------------------------------
    bool CanOpen(const std::pair<std::string, std::string>& aLocksStr);// 1877
    //-----------------------------------------------------------------------------
    bool BerryWeight(const std::vector<std::string>& aWeighingResStr, std::pair<std::size_t, std::size_t>& aBerrysWeight);// 2001
    //-----------------------------------------------------------------------------
    std::pair<bool, std::size_t> NecessarySeconds(std::string& aStr);// 1264
    //-----------------------------------------------------------------------------
    std::pair<bool, std::size_t> RestOfCar(std::vector<std::string> aStrs);//1787
    //-----------------------------------------------------------------------------
    std::size_t SteakCookingTime(std::string aStr);//1820
    //-----------------------------------------------------------------------------
    std::string MinPossibleNumber(std::size_t a, std::size_t b, std::size_t c);//2066
    //-----------------------------------------------------------------------------
    std::vector<std::size_t> PossibleChessHorseMovment(const std::vector<std::string>& aStrs);
    //-----------------------------------------------------------------------------
}
