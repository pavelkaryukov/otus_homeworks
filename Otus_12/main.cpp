#include "bulk_server.h"
#include <boost/format.hpp>

std::pair<std::size_t, std::size_t> GetArgs(int argc, char** argv) {
    const std::size_t kDefaultPort = 753;
    const std::size_t kDefaultBulkSize = 3;

    if (argc <= 1) {
        std::cout << "Порт не был установлен. Установлено  значение по умолчанию = " << kDefaultPort << std::endl;
        std::cout << "Количество команд в одной куче (bulk) не было установлено. Установлено  значение по умолчанию = " << kDefaultBulkSize << std::endl;
        return { kDefaultPort , kDefaultBulkSize };
    }

    const std::size_t port = std::atoi(argv[1]);
    if (port <= 0) {
        std::cout << "Значение Порта не валидно. Установлено  значение по умолчанию = " << kDefaultPort << std::endl;
        std::cout << "Количество команд в одной куче (bulk) не было установлено. Установлено  значение по умолчанию = " << kDefaultBulkSize << std::endl;
        return { kDefaultPort , kDefaultBulkSize };
    }

    if (argc < 3) {
        std::cout << "Количество команд в одной куче (bulk) не было установлено. Установлено  значение по умолчанию = " << kDefaultBulkSize << std::endl;
        return { port , kDefaultBulkSize };
    }

    const std::size_t bulkSize = std::atoi(argv[2]);
    if (bulkSize <= 0) {
        std::cout << "Количество команд в потоков записи файла не было установлено. Установлено  значение по умолчанию = " << kDefaultBulkSize << std::endl;
        return { port , kDefaultBulkSize };
    }

    return { port , bulkSize };
}


int main(int argc, char** argv) {
    //std::locale::global(std::locale(""));
    const auto[port, bulkSize] = GetArgs(argc, argv);
    std::cout << boost::format("Bulk server was started on port = [%1%], with bulk size = [%2%]") % port % bulkSize << std::endl;
    try {
        boost::asio::io_context io_context;

        BulkServer server(io_context, port, bulkSize);

        io_context.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }
    return 0;
}