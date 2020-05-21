#include "dispatcher/dispatcher.h"
#include <boost/format.hpp>
#include <sstream>
#include <chrono> 
#include <fstream>
#include <string> 
#include <time.h>

void MakeTestIter(const std::size_t aThreadsNumber, const std::size_t aCommandsNumber) {
    std::stringstream ss;
    {
        CommandDispatcher dispatcher{ 10, ss, aThreadsNumber };
        for (auto i = 0U; i < aCommandsNumber; ++i) {
            std::string str = boost::str(boost::format("cmd_%1%") % i);
            dispatcher.ProcessCmdLine(str);
        }
        dispatcher.Flush();
    }
}

void MakeTest() {
    auto createTime = time(nullptr);
    std::string filename = boost::str(boost::format("time_compare_%1%.txt") % createTime);
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::logic_error("MakeTest(): can't create file");
    }
    const std::size_t kCommandsNumber = 50000;
    std::string str1 = boost::str(boost::format("Кол-во команд=[%1%], команд в блоке = [10]\n") % kCommandsNumber);
    file << str1;
    for (auto threadsNum = 1U; threadsNum <= 64; ++threadsNum) {
        std::string str = boost::str(boost::format("%1%.Кол-во ниток=[%2%]\n") % threadsNum % threadsNum);
        auto start = std::chrono::high_resolution_clock::now();
        MakeTestIter(threadsNum, kCommandsNumber);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        str += boost::str(boost::format("  Время работы=[%1%] миллисекунд.\n") % duration.count());
        file << str;
        std::cout << "Threads=" << threadsNum << std::endl;
    }
}



int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    MakeTest();
    return 0;

    std::size_t N = 0;
    if (argc == 1) {
        std::cout << "Количество команд в одной куче (bulk) не было установлено. Установлено  значение по умолчанию = 3" << std::endl;
        N = 3;
    }
    else {
        N = std::atoi(argv[1]);
        if (N <= 0) {
            std::cout << "Количество команд в одной куче (bulk) имеет не валидное значение [" << argv[1] << "]. Установлено  значение по умолчанию = 3" << std::endl;
            N = 3;
        }
    }

    const std::size_t kBulkSize = N > 0 ? N : 1; // кол-во команда в одной булке

    {
        CommandDispatcher dispatcher{ kBulkSize, std::cout, 2};
        std::string str;
        std::cout << boost::format("Main Thread ID =[%1%]") % std::this_thread::get_id() << std::endl;
        while (std::getline(std::cin, str)) {
            if (str == "off")
                break;
            try {
                dispatcher.ProcessCmdLine(str);
            }
            catch (std::exception& e) {
                std::cout << "Exception:" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Program \"bulk\" Terminate" << std::endl;
                return 0;
            }
        }
        dispatcher.Flush(); //Подумать, что можно сделать, что бы программа не взрывалась
    }
    return 0;
}
