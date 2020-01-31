#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include "acm_timus/acm_timus.h"
#include "bin_pow/bin_pow.h"
#include "ip_filter/ip_filter.h"
#include "md5/md5.h"
//-----------------------------------------------------------------------------
void  Test()
{
    bin_pow::BinPowTest();
    auto res = ip_filter::SortAndFilterIPv4ForOtus("ip_filter-12995-758870.tsv");
    auto md5Sum = md5(res);
    bool test = md5Sum == "24e7a7b2270daee89c64d3ca5fb3da1a";
}
//-----------------------------------------------------------------------------
int main()
{
    Test();
    try {
        std::string line;
        ip_filter::IpList ipv4List;
        while (std::getline(std::cin, line)) {
            ip_filter::FillIpVect(line, ipv4List);
        }
        auto res = ip_filter::SortAndFilterIPv4ForOtus(ipv4List);
        if (!res.empty()) {
            std::cout << "Filtered and sorted IPv4 List:" << std::endl;
            std::cout << res << std::endl;
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}