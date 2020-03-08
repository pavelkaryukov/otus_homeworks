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
    MyIP::PrintIpAddr(MyIP::ToStr<decltype(test1)>(test1));
    MyIP::PrintIpAddr(MyIP::ToStr<decltype(test2)>(test2));
    MyIP::PrintIpAddr(MyIP::ToStr<decltype(test3)>(test3));
    MyIP::PrintIpAddr(MyIP::ToStr<decltype(test4)>(test4));
}
//-----------------------------------------------------------------------------
int main(int, char *[])
{
    PrintForOtus();
    return 0;
}
//-----------------------------------------------------------------------------

