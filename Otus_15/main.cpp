#include <fstream>
#include <iostream>
#include <string>
#include <boost/format.hpp>
 

std::size_t GetClusterNum(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Установлено количество кластеров по умолчанию = 1" << std::endl;
        return 1;
    }
    auto num = std::atoi(argv[1]);
    if (num <= 0) {
        std::cout << "Установлено количество кластеров по умолчанию = 1" << std::endl;
        return 1;
    }
    return num;
}

int main(int argc, char** argv) {
    const auto clusters = GetClusterNum(argc, argv);
    std::string str;
    std::ofstream file("test.txt");
    if (!file || !file.is_open()) {
        return 1;
    }

    while (std::getline(std::cin, str)){
        file << str << std::endl;
    }
    file << boost::format("Number of clusters = [%1%]") % clusters << std::endl; //TODO::DELETE
    file << "file end" << std::endl; //TODO::DELETE
    return 0;
}