#include "rsubd/rsubd.h"
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

int main(int argc, char** argv) {
    std::locale::global(std::locale(""));
    Test();
    return 0;
}