#include "mapper/my_mapper.h" 
#include "mapper/hasher/hasher_crc32.h"
#include "mapper/hasher/hasher_string.h"
#include "file_splitter/file_splitter.h"
#include "map_reduce/map_reduce.h"
#include "reducer/reducer.h"
#include <vector> 
#include <limits>
//TODO:: Передача функтора
//TODO:: Сделать Thread Pool

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

void Test3() {
    std::filesystem::path fpath = { "c:\\my_programs\\otus\\otus_homeworks_all_2\\ip\\GeoIPCountryWhois.csv" };
    auto str = fpath.filename();
    auto blocks = file_split::GetBlocksFromFile(fpath, 10);
    std::ifstream file(fpath, std::ios::binary);

    if (!file || !file.is_open())
        throw std::logic_error("");
    std::size_t partNum = 0;

    for (const auto& block : blocks) {
        file_split::SaveFilePart(file, block, partNum++);
    }
}

void Test4() {
    std::filesystem::path fpath = { "c:\\my_programs\\otus\\otus_homeworks_all_2\\ip\\GeoIPCountryWhois.csv" };
    using hash_t = std::string;
    using hashFactory_t = boost::factory<std::unique_ptr<HasherString>>;
    using map_t = std::map<hash_t, std::size_t>;

    MapReduce<hash_t> mapReducer{ hashFactory_t(), 10,  16, ReduceFunc<hash_t>};
    mapReducer.Process(fpath);
    int stop1 = 0;
}


int main(int argc, char** argv) {
    Test4();
    return 0;
}