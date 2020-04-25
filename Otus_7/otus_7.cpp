#include "dispatcher/dispatcher.h"

int main(int argc, char** argv) {
    std::size_t N = 0;
    if (argc == 1) {
        std::cout << "Commands number in one bulk did not set, default value was set = 3" << std::endl;
        N = 3;
    }
    else {
        N = std::atoi(argv[1]);
    }
    const std::size_t kBulkSize = N > 0 ? N : 1; // кол-во команда в одной булке
    CommandDispatcher dispatcher{ kBulkSize };
    std::string str;
    while (std::getline(std::cin, str)) {
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
    return 0;
}
