//#include "rsubd/rsubd.h"
#include "rsubd/cmd_performer.h"
#include "dispatcher/dispatcher.h"

void Test() {
    RSUBD mySubd;
    auto code1 = mySubd.Insert("A", { { 1, "perchik" } });
    auto code2 = mySubd.Insert("A", { { 2, "ahperchik" } });
    auto code21 = mySubd.Insert("A", { { 22, "durachok" } });
    auto code12 = mySubd.Insert("A", { { 13, "dzhigurda" } });
    auto code13 = mySubd.Insert("B", { { 13, "antoshka" } });
    auto code3 = mySubd.Insert("B", { { 1, "amdass" } });
    auto code4 = mySubd.Insert("B", { { 4, "dass" } });
    auto code5 = mySubd.Insert("B", { { 1, "durak" } });
    auto code6 = mySubd.Insert("Z", { { 1, "durak" } });
    auto intersection = mySubd.Intersection();
    auto symmetric = mySubd.SimmetricDifference();
    auto code7 = mySubd.Truncate("z");
    auto code8 = mySubd.Truncate("A");
    auto code9 = mySubd.Truncate("B");
    int stop1 = 0;
}

void Test2() {
    CmdPerformer interpretarot;
    auto str1 = interpretarot.ProcessCommand("INSERT A 0 lean");
    auto str2 = interpretarot.ProcessCommand("INSERT A 2");
    auto str3 = interpretarot.ProcessCommand("INsERT A 2");
    auto str4 = interpretarot.ProcessCommand("INSERT Z 21");
    auto str5 = interpretarot.ProcessCommand("INSERT B 2 ahper");
    auto str6 = interpretarot.ProcessCommand("INSERT B 3 ahmustafa");
    auto str7 = interpretarot.ProcessCommand("INSERT B 2 dzhigurde");

    auto str13 = interpretarot.ProcessCommand("INTERSECTION");
    auto str12 = interpretarot.ProcessCommand("SYMMETRIC_DIFFERENCE");

    auto str9  = interpretarot.ProcessCommand("TRUNCATE Z");
    auto str10 = interpretarot.ProcessCommand("TRUNCATE A");
    auto str11 = interpretarot.ProcessCommand("TRUNCATE B");
    int stop1 = 0;
}


void Test3() {
    std::cout << boost::format("main thread id=[%1%]") % std::this_thread::get_id() << std::endl;
    auto printMutex = std::make_shared<std::mutex>();
    DispatherSUBD executor1{std::cout, printMutex};
    DispatherSUBD executor2{std::cout, printMutex};

    executor1.ProcessCommand("INSERT A 0 lean");
    executor1.ProcessCommand("INSERT A 2");
    executor1.ProcessCommand("INsERT A 2");
    executor1.ProcessCommand("INSERT Z 21");
    executor1.ProcessCommand("INSERT B 2 ahper");
    executor1.ProcessCommand("INSERT B 3 ahmustafa");
    executor1.ProcessCommand("INSERT B 2 dzhigurde");

    executor1.ProcessCommand("INTERSECTION");
    executor1.ProcessCommand("SYMMETRIC_DIFFERENCE");

    executor1.ProcessCommand("TRUNCATE Z");
    executor1.ProcessCommand("TRUNCATE A");
    executor1.ProcessCommand("TRUNCATE B");
    
    executor2.ProcessCommand("INSERT A 0 lean");
    executor2.ProcessCommand("INSERT A 2");
    executor2.ProcessCommand("INsERT A 2");
    executor2.ProcessCommand("INSERT Z 21");
    executor2.ProcessCommand("INSERT B 2 ahper");
    executor2.ProcessCommand("INSERT B 3 ahmustafa");
    executor2.ProcessCommand("INSERT B 2 dzhigurde");

    executor2.ProcessCommand("INTERSECTION");
    executor2.ProcessCommand("SYMMETRIC_DIFFERENCE");

    executor2.ProcessCommand("TRUNCATE Z");
    executor2.ProcessCommand("TRUNCATE A");
    executor2.ProcessCommand("TRUNCATE B");

    executor1.Exit();                                                                     
    executor2.Exit();
    std::cout << boost::format("main thread id=[%1%]") % std::this_thread::get_id() << std::endl;
    int stop1 = 0;
}

int main(int argc, char** argv) {
    std::locale::global(std::locale(""));
    Test3();
    return 0;
}