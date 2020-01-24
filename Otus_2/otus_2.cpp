#include <iostream>
#include <string>
#include "acm_timus/acm_timus.h"

#include <fstream>
#include <iostream>
#include <type_traits>
#include "bin_pow/bin_pow.h"
#include <assert.h>
//-----------------------------------------------------------------------------
void AcmTimusTaskExecute()
{
    //task 1000
    auto task1000 = acm_timus::Sum(5, 1);
    //task 1001
    std::ifstream testFile("c:\\my_programs\\otus\\otus_homeworks\\Otus_2\\task1001.txt"); // ѕеределать путь на относительный (думаю пусть cmake копирует в папку с бинарниками)
    std::string str, allStr;
    while (std::getline(testFile, str)) {
        allStr += str;
    }
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
    //TODO:: ¬ывод в командную строку на английском €зыке
}
//-----------------------------------------------------------------------------
void BinPowTest()
{
    //const auto test = GetMinBinPow(1);
    static_assert(bin_pow::Step(5, 2));
    static_assert(bin_pow::BinExp(4));
    static_assert(bin_pow::GetMinBinPow(4));
    static_assert(bin_pow::GetMinBinPow(0) == 0);
    static_assert(bin_pow::GetMinBinPow(1) == 0);
    static_assert(bin_pow::GetMinBinPow(2) == 1);
    static_assert(bin_pow::GetMinBinPow(4) == 2);
    static_assert(bin_pow::GetMinBinPow(7) == 3);
    static_assert(bin_pow::GetMinBinPow(8) == 3);
    static_assert(bin_pow::GetMinBinPow(9) == 4);
    static_assert(bin_pow::GetMinBinPow(1023) == 10);
    static_assert(bin_pow::GetMinBinPow(1024) == 10);
    static_assert(bin_pow::GetMinBinPow(1025) == 11);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 - 33) == 20);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024) == 20);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 + 33) == 21);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 * 1024 - 127) == 30);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 * 1024) == 30);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 * 1024 + 127) == 31);
}
//-----------------------------------------------------------------------------
int main()
{
    AcmTimusTaskExecute();
    BinPowTest();
    return 0;
}