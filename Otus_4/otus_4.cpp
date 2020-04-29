#include "ip_to_str.h"
#include <array>
#include <list>
#include <vector>
//-----------------------------------------------------------------------------
void PrintForOtus()
{
    auto test1 = char(-1);
    auto test2 = short(0);
    auto test3 = int(2130706433);
    auto test4 = std::uint64_t(8875824491850138409);
    MyIP::PrintIpAddr(MyIP::ToStr(test1));
    MyIP::PrintIpAddr(MyIP::ToStr(test2));
    MyIP::PrintIpAddr(MyIP::ToStr(test3));
    MyIP::PrintIpAddr(MyIP::ToStr(test4));

    std::array <int, 4> array1 = { 1, 12, 25, 67 };
    std::vector<int>    vect1 = { 1, 12, 25, 67 };
    std::list  <int>    list1 = { 1, 12, 25, 67 };
    MyIP::PrintIpAddr(MyIP::ToStr(array1));
    MyIP::PrintIpAddr(MyIP::ToStr(array1));
    MyIP::PrintIpAddr(MyIP::ToStr(vect1));

    std::tuple<int, int, int> tuple1 = { 1, 12, 25 };
    MyIP::PrintIpAddr(MyIP::ToStr(tuple1));
    auto str = std::string("pish pish ololo");
    MyIP::PrintIpAddr(MyIP::ToStr(str, MyIP::ByteOrder::BigEndian));
    MyIP::PrintIpAddr(MyIP::ToStr(str, MyIP::ByteOrder::LittleEndian));

    MyIP::PrintIpAddr(MyIP::ToStr<MyIP::ByteOrder::BigEndian>(str));
    MyIP::PrintIpAddr(MyIP::ToStr<MyIP::ByteOrder::LittleEndian>(str));
    int stop1 = 0;
}
//-----------------------------------------------------------------------------
int main(int, char *[])
{
    PrintForOtus();
    return 0;
}
//-----------------------------------------------------------------------------

