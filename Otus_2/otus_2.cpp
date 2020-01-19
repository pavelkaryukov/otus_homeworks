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
}

int main()
{
    AcmTimusTaskExecute();
    return 0;
}