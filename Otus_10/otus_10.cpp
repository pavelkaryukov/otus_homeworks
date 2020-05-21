#include "dispatcher/dispatcher.h"

std::pair<std::size_t, std::size_t> GetArgs(int argc, char** argv) {
    const std::size_t kDefaultBulkSize  = 3;
    const std::size_t kDefaultThreadNum = 2;

    if (argc <= 1) {
        std::cout << "Количество команд в одной куче (bulk) не было установлено. Установлено  значение по умолчанию = " << kDefaultBulkSize << std::endl;
        std::cout << "Количество команд в потоков записи файла не было установлено. Установлено  значение по умолчанию = " << kDefaultThreadNum << std::endl;
        return { kDefaultBulkSize , kDefaultThreadNum };
    }

    const std::size_t bulkSize = std::atoi(argv[1]);
    if (bulkSize <= 0) {
        std::cout << "Количество команд в одной куче (bulk) не было установлено. Установлено  значение по умолчанию = " << kDefaultBulkSize << std::endl;
        std::cout << "Количество команд в потоков записи файла не было установлено. Установлено  значение по умолчанию = " << kDefaultThreadNum << std::endl;
        return { kDefaultBulkSize , kDefaultThreadNum };
    } 

    if (argc < 3) {
        std::cout << "Количество команд в потоков записи файла не было установлено. Установлено  значение по умолчанию = " << kDefaultThreadNum << std::endl;
        return { bulkSize , kDefaultThreadNum };
    }

    const std::size_t threadsNum = std::atoi(argv[2]);
    if (threadsNum <= 0) {
        std::cout << "Количество команд в потоков записи файла не было установлено. Установлено  значение по умолчанию = " << kDefaultThreadNum << std::endl;
        return { bulkSize , kDefaultThreadNum };
    }

    return { bulkSize , threadsNum };
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    const auto[bulkSize, threadsNum] = GetArgs(argc, argv);

    {
        std::shared_ptr<std::mutex> outMutex = std::make_shared<std::mutex>();
        CommandDispatcher dispatcher{ bulkSize, std::cout, threadsNum, outMutex };
        std::string str;
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
