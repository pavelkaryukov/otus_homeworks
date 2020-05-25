//#include "rsubd/rsubd.h"
#include "rsubd/cmd_performer.h"
#include "server/join_server.h"

std::size_t GetPortFromArgs(int argc, char** argv) {
    const std::size_t kDefaultPort = 754;

    if (argc <= 1) {
        std::cout << "Порт не был установлен. Установлено  значение по умолчанию = " << kDefaultPort << std::endl;
        return kDefaultPort;
    }

    const std::size_t port = std::atoi(argv[1]);
    if (port <= 0) {
        std::cout << "Значение Порта не валидно. Установлено  значение по умолчанию = " << kDefaultPort << std::endl;
        return kDefaultPort;
    }
    return kDefaultPort;
}


int main(int argc, char** argv) {
    std::locale::global(std::locale(""));
    try {
        const std::size_t port = GetPortFromArgs(argc, argv);
        std::cout << boost::format("Сервер будет запущен на порту = [%1%]") % port << std::endl;
        boost::asio::io_context io_context;
        auto printMutex = std::make_shared<std::mutex>();
        JoinServer server(io_context, port, printMutex, std::cout);
        io_context.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }

    return 0;
}