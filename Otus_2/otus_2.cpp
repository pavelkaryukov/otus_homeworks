#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include "acm_timus/acm_timus.h"
#include "bin_pow/bin_pow.h"
#include "ip_filter/ip_filter.h"
//-----------------------------------------------------------------------------
int main()
{
    acm_timus::AcmTimusTaskExecute();
    bin_pow::BinPowTest();
    ip_filter::TestFunc();
//     for (std::string line; std::getline(std::cin, line);) {
//         int  i = 0;
//     }

    return 0;
}