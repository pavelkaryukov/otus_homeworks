#pragma once
#include <string>

namespace acm_timus
{
    std::string GrishaCanSolve(const std::string& aSolvedInFirstHourTasksStr);
    //-----------------------------------------------------------------------------
    std::pair<bool, std::string> ToLocalizedStr(const std::string& aStr); //Task 1785
    //-----------------------------------------------------------------------------
    std::string InvSqr(std::string Str);//Task 1001
    //-----------------------------------------------------------------------------
    template<typename T>
    T Sum(T a, T b) // Task 1000
    {
        return a + b;
    }
    //-----------------------------------------------------------------------------
}
