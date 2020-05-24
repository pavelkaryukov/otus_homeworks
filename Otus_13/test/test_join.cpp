#include <gtest/gtest.h> // googletest header file
#include "dispatcher/dispatcher.h"
#include <sstream>
#include <fstream>

std::stringstream MakeExpected() {
     const std::vector<std::string> kStrs = {
         "OK",
         "OK",
         "ERROR: Unknown command [INsERT]",
         "ERROR: [Таблица не существует]",
         "OK",
         "OK",
         "ERROR: [Кортеж с этим id уже существет]",
         "2,,Puskin",
         "OK",
         "",
         "0,Tolstoy,",
         "3,,Lermontov",
         "OK",
         "",
         "ERROR: [Таблица не существует]",
         "OK",
         "OK"
     };    
    std::stringstream ss;
     for (const auto& str : kStrs ){
         ss << str << std::endl;
     }
    return ss;
}
TEST(test_join, test_dispatcher) {
    auto printMutex = std::make_shared<std::mutex>();
    std::stringstream ss;
    {
        DispatherSUBD executor1{ ss, printMutex };

        executor1.ProcessCommand("INSERT A 0 Tolstoy");
        executor1.ProcessCommand("INSERT A 2");
        executor1.ProcessCommand("INsERT A 2");
        executor1.ProcessCommand("INSERT Z 21");
        executor1.ProcessCommand("INSERT B 2 Puskin");
        executor1.ProcessCommand("INSERT B 3 Lermontov");
        executor1.ProcessCommand("INSERT B 2 Dostaevskii");

        executor1.ProcessCommand("INTERSECTION");
        executor1.ProcessCommand("SYMMETRIC_DIFFERENCE");

        executor1.ProcessCommand("TRUNCATE Z");
        executor1.ProcessCommand("TRUNCATE A");
        executor1.ProcessCommand("TRUNCATE B");
        executor1.Exit();
    }
    
    auto str = ss.str();
    auto str2 = MakeExpected().str();
    {
        std::ofstream fout1("str1.txt"), fout2("str2.txt");
        fout1 << str;
        fout2 << str2;
    }
    ASSERT_TRUE(str == str2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}