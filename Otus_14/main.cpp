//#include "mapper/my_mapper.h" 
//#include "mapper/hasher/hasher_crc32.h"
//#include "mapper/hasher/hasher_string.h"
//#include "file_splitter/file_splitter.h"
//#include "map_reduce/map_reduce.h"
//#include "reducer/reducer.h"
//#include <vector> 
//#include <limits>
#include "prefix_finder/prefix_finder.h"

int main(int argc, char** argv) {
    std::locale::global(std::locale(""));
    auto prefixSize = GetPrefixSize({ "c:\\my_programs\\otus\\otus_homeworks_all_2\\ip\\GeoIPCountryWhois.csv" }, 10, 6);
    std::cout << boost::format("Минимальный размер префикса = [%1%]") % prefixSize << std::endl;
    return 0;
}