#include <iostream>
#include "command/simple_command.h"
#include "dispatcher/dispatcher.h"
//ѕодруби буст fmt

int TestDispatcher() {
    CommandDispatcher dispatcher{3};
    dispatcher.ProcessCmdLine("cmd1");
    dispatcher.ProcessCmdLine("}");
    dispatcher.ProcessCmdLine("}");
    dispatcher.ProcessCmdLine("cmd2");
    dispatcher.ProcessCmdLine("cmd3");
    dispatcher.ProcessCmdLine("cmd33");
    dispatcher.ProcessCmdLine("{");
    dispatcher.ProcessCmdLine("cmd4");
    dispatcher.ProcessCmdLine("cmd5");
    dispatcher.ProcessCmdLine("{");
    dispatcher.ProcessCmdLine("cmd6");
    dispatcher.ProcessCmdLine("cmd7");
    dispatcher.ProcessCmdLine("cmd8");
    dispatcher.ProcessCmdLine("}");
    dispatcher.ProcessCmdLine("}");


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


