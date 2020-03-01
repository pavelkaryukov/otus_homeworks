#include "ip_to_str.h"
#include <array>
 
//-----------------------------------------------------------------------------
int main(int, char *[])
{
    std::array<int, 4>  test1 = { 1, 12, 33, 44 };
    std::array<int, 3>  test2 = { 1, 12, 33};
    std::array<int, 4>  test3 = { 1, 12, 256, 0 };
    std::array<int, 88> test4 = { 1};
    auto str1 = MyIPv4::ToStr(test1);
    auto str2 = MyIPv4::ToStr(test2);
    auto str3 = MyIPv4::ToStr(test3);
    auto str4 = MyIPv4::ToStr(test4);

    auto str13 = MyIPv4::ToStr(test1, MyIPv4::ByteOrder::LittleEndian);
    auto str23 = MyIPv4::ToStr(test2, MyIPv4::ByteOrder::LittleEndian);
    auto str33 = MyIPv4::ToStr(test3, MyIPv4::ByteOrder::LittleEndian);
    auto str43 = MyIPv4::ToStr(test4, MyIPv4::ByteOrder::LittleEndian);


    int test12 = 0x01'0f'ff'02;
    auto str12 = MyIPv4::ToStr(test12);
    auto str15 = MyIPv4::ToStr(test12, MyIPv4::ByteOrder::LittleEndian);
    int otus_1 = 1234;
    auto stra1 = MyIPv4::ToStr(otus_1);
    auto stra2 = MyIPv4::ToStr(otus_1, MyIPv4::ByteOrder::LittleEndian);
    auto str22 = MyIPv4::ToStr("MyTEstString");
    std::tuple<int, int, int, int> tuple1 = { 1, 12, 25, 67 };
    std::tuple<int, short, long long/*, int*/> tuple2 = { 1, 12, 25/*, 67 */};
    auto str612 = MyIPv4::ToStr(tuple1, MyIPv4::ByteOrder::BigEndian);
    auto str613 = MyIPv4::ToStr(tuple1, MyIPv4::ByteOrder::LittleEndian);
    auto str622 = MyIPv4::ToStr(tuple2);

    return 0;
}
//-----------------------------------------------------------------------------

