#include <gtest/gtest.h> // googletest header file
#include "dispatcher/dispatcher.h"
#include <boost/algorithm/string.hpp>
#include <sstream>

TEST(test_bulk, test_bulk_invalid_data) {
    std::string expectedStr = "bulk: {{{, cmd1, cmd2";
    std::stringstream ss;
    CommandDispatcher dispatcher{ 3, ss };
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
    std::string outputStr = ss.str();
    boost::erase_all(outputStr, "\r");
    boost::erase_all(outputStr, "\n");
    ASSERT_STRCASEEQ(expectedStr.c_str(), outputStr.c_str());
}

TEST(test_bulk, test_bulk_valid_data) {
    //bulk: cmd1, cmd2, cmd3
    //bulk : cmd33
    //bulk : cmd4, cmd5, cmd6, cmd7, cmd8
    //bulk : cmd26, cmd27, cmd28

    std::string expectedStr = "bulk: cmd1, cmd2, cmd3";
    expectedStr += "bulk: cmd33";
    expectedStr += "bulk: cmd4, cmd5, cmd6, cmd7, cmd8";
    expectedStr += "bulk: cmd26, cmd27, cmd28";
    expectedStr += "bulk: cmd29, cmd20";

    std::stringstream ss;
    CommandDispatcher dispatcher{ 3, ss };
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
    std::string outputStr = ss.str();
    boost::erase_all(outputStr, "\r");
    boost::erase_all(outputStr, "\n");
    ASSERT_STRCASEEQ(expectedStr.c_str(), outputStr.c_str());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}