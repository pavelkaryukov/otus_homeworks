#include <iostream>
#include <string>
#include "acm_timus/acm_timus.h"

#include <fstream>
#include <iostream>

void AcmTimusTaskExecute()
{
    //task 1000
    auto task1000 = acm_timus::Sum(5, 1);
    //task 1001
    std::ifstream testFile("c:\\my_programs\\otus\\otus_homeworks\\Otus_2\\task1001.txt"); // Переделать путь на относительный (думаю пусть cmake копирует в папку с бинарниками)
    std::string str, allStr;
    while (std::getline(testFile, str)) {
        allStr += str;
    }
    auto task1001 = acm_timus::InvSqr(allStr);
    auto task1785a = acm_timus::ToLocalizedStr("7");
    auto task1785b = acm_timus::ToLocalizedStr("7.2");
    auto task1785c = acm_timus::ToLocalizedStr("400");
    auto task1785d = acm_timus::ToLocalizedStr("40");
    auto task1785f = acm_timus::ToLocalizedStr("0");
    auto task2012a = acm_timus::GrishaCanSolve("7");
    auto task2012b = acm_timus::GrishaCanSolve("5");
    auto task2012c = acm_timus::GrishaCanSolve("s7");
    auto task2012d = acm_timus::GrishaCanSolve("70");
}

int main()
{
    AcmTimusTaskExecute();
    return 0;
}