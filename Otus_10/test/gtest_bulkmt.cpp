#include <gtest/gtest.h> // googletest header file
#include "dispatcher/dispatcher.h"
#include <sstream>

 TEST(test_bulk, test_bulkmt_invalid_data) {
     std::stringstream expectedSS;
     expectedSS << "bulk: {{{, cmd1, cmd2"                       << std::endl;
     expectedSS << "main stream: 13 lines, 1 blocks, 3 commands" << std::endl;
     expectedSS << "log thread: 1 - blocks, 3 - commands"        << std::endl;
     expectedSS << "file_1 thread: 0 - blocks, 0 - commands"     << std::endl;
     expectedSS << "file_2 thread: 1 - blocks, 3 - commands"     << std::endl;

     std::stringstream ss;
     {
         CommandDispatcher dispatcher{ 3, ss, 2 };
         dispatcher.ProcessCmdLine("{{{");
         dispatcher.ProcessCmdLine("cmd1");
         dispatcher.ProcessCmdLine("cmd2");
         dispatcher.ProcessCmdLine("{");
         dispatcher.ProcessCmdLine("{");
         dispatcher.ProcessCmdLine("{");
         dispatcher.ProcessCmdLine("}");
         dispatcher.ProcessCmdLine("}");
         dispatcher.ProcessCmdLine("}");
         dispatcher.ProcessCmdLine("{");
         dispatcher.ProcessCmdLine("}");
         dispatcher.ProcessCmdLine("{");
         dispatcher.ProcessCmdLine("}");
         dispatcher.Flush();
     }
     std::string outputStr = ss.str();
     std::string expectedStr = expectedSS.str();
     ASSERT_STRCASEEQ(expectedStr.c_str(), outputStr.c_str());
 }

TEST(test_bulkmt, test_bulkmt_valid_data) {
    std::stringstream expectedSS;

    expectedSS << "bulk: cmd1, cmd2, cmd3"             << std::endl;
    expectedSS << "bulk: cmd33"                        << std::endl;
    expectedSS << "bulk: cmd4, cmd5, cmd6, cmd7, cmd8" << std::endl;
    expectedSS << "bulk: cmd26, cmd27, cmd28"          << std::endl;
    expectedSS << "bulk: cmd29, cmd20"                 << std::endl;
    expectedSS << "main stream: 20 lines, 5 blocks, 14 commands" << std::endl;
    expectedSS << "log thread: 5 - blocks, 14 - commands" << std::endl;
    expectedSS << "file_1 thread: 2 - blocks, 4 - commands" << std::endl;
    expectedSS << "file_2 thread: 3 - blocks, 10 - commands" << std::endl;

    std::stringstream ss;
    {
        CommandDispatcher dispatcher{ 3, ss, 2 };
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
        dispatcher.ProcessCmdLine("cmd26");
        dispatcher.ProcessCmdLine("cmd27");
        dispatcher.ProcessCmdLine("cmd28");
        dispatcher.ProcessCmdLine("cmd29");
        dispatcher.ProcessCmdLine("cmd20");
        dispatcher.Flush();
    }
    std::string outputStr = ss.str();
    std::string expectedStr = expectedSS.str();

    ASSERT_STRCASEEQ(expectedStr.c_str(), outputStr.c_str());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}