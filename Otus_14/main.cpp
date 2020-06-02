#include "prefix_finder/prefix_finder.h"
#include <filesystem>

struct Args {
    std::filesystem::path FileName;
    std::size_t ThreadsMap = 1;
    std::size_t ThreadsReduce = 1;
};

Args GetArgs(int argc, char** argv) {
    if (argc == 1)
        throw std::invalid_argument("Отсутсвует имя файла");
    Args res;
    res.FileName = { std::string(argv[1]) };
    if (!std::filesystem::exists(res.FileName))
        throw std::invalid_argument(boost::str(boost::format("Файл с именем [%1%] отсутсвует") % res.FileName));

    if (argc >= 3) {
        auto thrMap = std::atoi(argv[2]);
        if (thrMap <= 0) {
            std::cout << boost::format("Не валидное количество Map потоков = [%1%], установленно значение по умолчанию=[%2%]")
                % std::string(argv[2]) % res.ThreadsMap;
        }
        else {
            res.ThreadsMap = thrMap;
        }
    }
    
    if (argc >= 4) {
        auto redMap = std::atoi(argv[3]);
        if (redMap <= 0) {
            std::cout << boost::format("Не валидное количество Reduce потоков = [%1%], установленно значение по умолчанию=[%2%]")
                % std::string(argv[2]) % res.ThreadsReduce;
        }
        else {
            res.ThreadsReduce= redMap;
        }
    }

    return res;
}

int main(int argc, char** argv) {
    std::locale::global(std::locale(""));
    try {
        auto args = GetArgs(argc, argv);
        auto prefixSize = GetPrefixSize(args.FileName, args.ThreadsMap, args.ThreadsReduce);
        std::cout << boost::format("Минимальный размер префикса = [%1%]") % prefixSize << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    //"c:\\my_programs\\otus\\otus_homeworks_all_2\\ip\\GeoIPCountryWhois.csv"
    return 0;
}