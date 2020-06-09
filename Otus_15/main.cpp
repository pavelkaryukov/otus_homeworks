#include "clustering.h"
#include <fstream>
#include <string>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
using separator_t = boost::char_separator<char>;
using tokenizer_t = boost::tokenizer<separator_t>;
std::size_t GetClusterNum(int argc, char** argv) {
    const std::size_t defaultValue = 4;
    if (argc < 2) {
        std::cout << "Установлено количество кластеров по умолчанию = 1" << std::endl;
        return defaultValue;
    }
    auto num = std::atoi(argv[1]);
    if (num <= 0) {
        std::cout << "Установлено количество кластеров по умолчанию = 1" << std::endl;
        return defaultValue;
    }
    return num;
}

bool FillPair(cluster::coord_t& aCoord, std::vector<std::string>& aStrs) {
    if (aStrs.empty())
        return false;
    if (aStrs.size() < 2)
        return false;
    aCoord.first  = std::atof(aStrs[0].c_str());
    aCoord.second = std::atof(aStrs[1].c_str());
    return true;
}

int main(int argc, char** argv) {
    std::locale::global(std::locale(""));
    const auto clusters = GetClusterNum(argc, argv);
    std::string str;

    cluster::coord_t coord = {0, 0};
    std::vector<cluster::coord_t> coords;
    while (std::getline(std::cin, str)) {
        tokenizer_t tokenizer(str, separator_t(";\r\n"));
        std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());
        if (!FillPair(coord, tokens))
            continue;
        coords.push_back(coord);
    }
    std::ofstream outfile("result.txt");
    if (!outfile || !outfile.is_open()) {
        std::cout << "Не удается открыть файл для записи" << std::endl;
        return 1;
    }
    cluster::CalcClusters(coords, clusters, outfile);
    //тут процедура кластеризации
    return 0;
}