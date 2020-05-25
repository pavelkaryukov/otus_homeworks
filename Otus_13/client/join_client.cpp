#include <boost/asio.hpp>
#include <string>
#include <iostream>

namespace ba = boost::asio;

std::pair<std::string, std::size_t> GetArgs(int argc, char** argv) {
    const std::string kDefaultIP = "127.0.0.1";
    const std::size_t kDefaultPort = 754;

    if (argc <= 1) {
        std::cout << "IP не был установлен. значение по умолчанию = " << kDefaultIP<< std::endl;
        std::cout << "Port не был установлен, значение по умолчанию = " << kDefaultPort << std::endl;
        return { kDefaultIP , kDefaultPort };
    }

    const std::string ip = std::string(argv[1]);
    if (argc < 3) {
        std::cout << "Port не был установлен, значение по умолчанию = " << kDefaultPort << std::endl;
        return { ip , kDefaultPort };
    }

    const std::size_t port = std::atoi(argv[2]);
    if (port <= 0) {
        std::cout << "Port не был установлен, значение по умолчанию = " << kDefaultPort << std::endl;
        return { ip , kDefaultPort };
    }

    return { ip , port };
}


int main(int argc, char** argv) {
    std::locale::global(std::locale(""));
    const auto[ipAddr, portAddr] = GetArgs(argc, argv);
    try {
        ba::io_context io_context;

        ba::ip::tcp::endpoint ep(
            ba::ip::address::from_string(
                ipAddr
            ),
            portAddr
        );
        ba::ip::tcp::socket sock(io_context);

        sock.connect(ep);

        std::string str;
        std::size_t counter = 0;
        while (std::getline(std::cin, str)) {
            str += '\n';
            ++counter;
            ba::write(sock, ba::buffer(str));
        };
    }
    catch(const boost::system::system_error& ex) {
        std::cout << "boost exception! " << ex.what() << std::endl;
    }
    catch(const std::exception& ex) {
        std::cout << "std::exception! " << ex.what() << std::endl;
    }

    return 0;
}
