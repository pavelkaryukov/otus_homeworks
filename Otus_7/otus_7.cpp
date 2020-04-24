#include <iostream>
#include "command/simple_command.h"
#include "dispatcher/dispatcher.h"
//ѕодруби буст fmt

int TestDispatcher() {
    CommandDispatcher dispatcher{0};
    dispatcher.AddCommand("cmd1");
    dispatcher.AddCommand("cmd2");
    dispatcher.AddCommand("cmd3");


    //dispatcher.ExecuteAll();
    return 0;
}

int main_test(int argc, char** argv) {
    std::size_t N = 0;
    if (argc == 1) {
        std::cout << "Pls, input N (commands number in one bulk)" << std::endl;
    }
    else {
        N = std::atoi(argv[1]);
    }
    const std::size_t kBulkSize = N; // кол-во команда в одной булке
    TestDispatcher();
    return 0;
}


int main(int argc, char** argv) {
    char* commands[] = { "c:\\Programs\\bulk.exe", "3" };
    main_test(2, commands);
    return 0;
}


