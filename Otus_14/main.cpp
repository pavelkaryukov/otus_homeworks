#include "mapper/my_mapper.h" 
#include "mapper/hasher/hasher_crc32.h"
#include "mapper/hasher/hasher_string.h"
#include <vector> 

void Test() {
    std::string str1 = "раз два три лети";
    std::string str2 = "раз два три лети";
    std::string str3 = "перчик ахперчик раз два три";
    HasherCRC mapperCrc;
    auto res1 = mapperCrc.CalcHash(str1.data(), str1.size());
    auto res2 = mapperCrc.CalcHash(str2.data(), str2.size());
    auto res3 = mapperCrc.CalcHash(str3.data(), str3.size());
    int stop1 = 0;
    HasherString mapperStr;
    auto res11 = mapperStr.CalcHash(str1.data(), str1.size());
    auto res21 = mapperStr.CalcHash(str2.data(), str2.size());
    auto res31 = mapperStr.CalcHash(str3.data(), str3.size());
    int stop11 = 0;
}

void Test2() {
    const std::vector<std::string> vect = {
        "раз два три лети"           ,
        "раз два три лети"           ,
        "перчик ахперчик раз два три"
    };

    Mapper<std::size_t> mapper1{ std::make_unique<HasherCRC>() };
    Mapper<std::string> mapper2{ std::make_unique<HasherString>() };

    auto hashes1 = mapper1.Calc(vect);
    auto hashes2 = mapper2.Calc(vect);
}

int main(int argc, char** argv) {
    Test();
    Test2();
    return 0;
}