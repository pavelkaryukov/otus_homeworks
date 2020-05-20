#include "bulk_server.h"
#include <boost/format.hpp>



int main(int argc, char** argv) {
    const std::size_t   kBulkSize = 3;  //TODO:: задать через командную строку
    const std::uint16_t kPort = 753;//TODO:: задать через командную строку

    std::cout << boost::format("Bulk server was started on port = [%1%], with bulk size = [%2%]") % kPort % kBulkSize << std::endl;
    try {
        boost::asio::io_context io_context;

        BulkServer server(io_context, kPort, kBulkSize);

        io_context.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }
    return 0;
}