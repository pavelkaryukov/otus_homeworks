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
    auto test4 = long long(8875824491850138409);
    MyIP::PrintIpAddr(MyIP::ToStr<decltype(test1)>(test1));
    MyIP::PrintIpAddr(MyIP::ToStr<decltype(test2)>(test2));
    MyIP::PrintIpAddr(MyIP::ToStr<decltype(test3)>(test3));
    MyIP::PrintIpAddr(MyIP::ToStr<decltype(test4)>(test4));

}
//-----------------------------------------------------------------------------
int main(int, char *[])
{
    PrintForOtus();
     //std::array<int, 4>  test1 = { 1, 12, 33, 44 };
     //std::array<int, 3>  test2 = { 1, 12, 33};
     //std::array<int, 4>  test3 = { 1, -1, 255, 0 };
 
     //auto res2222 = static_cast<std::size_t>(test3[1]);
     //std::array<int, 88> test4 = { 1};
     //auto str1 = MyIP::ToStr(test1);
     //auto str2 = MyIP::ToStr(test2);
     //auto str3 = MyIP::ToStr(test3);
     //auto str4 = MyIP::ToStr(test4);
 
     //auto str13 = MyIP::ToStr(test1, MyIP::ByteOrder::LittleEndian);
     //auto str23 = MyIP::ToStr(test2, MyIP::ByteOrder::LittleEndian);
     //auto str33 = MyIP::ToStr(test3, MyIP::ByteOrder::LittleEndian);
     //auto str43 = MyIP::ToStr(test4, MyIP::ByteOrder::LittleEndian);
 
 
     //int test12 = 0x01'0f'ff'02;
     //auto str12 = MyIP::ToStr(test12);
     //auto str15 = MyIP::ToStr(test12, MyIP::ByteOrder::LittleEndian);
     //int otus_1 = 1234;
     //auto stra1 = MyIP::ToStr(otus_1);
     //auto stra2 = MyIP::ToStr(otus_1, MyIP::ByteOrder::LittleEndian);
     //auto str22 = MyIP::ToStr("MyTEstString");
     //std::tuple<int, int, int, int> tuple1 = { 1, 12, 25, 67 };
     //std::tuple<int, short, long long/*, int*/> tuple2 = { 1, 12, 25/*, 67 */};
     //auto str612 = MyIP::ToStr(tuple1, MyIP::ByteOrder::BigEndian);
     //auto str613 = MyIP::ToStr(tuple1, MyIP::ByteOrder::LittleEndian);
     //auto str622 = MyIP::ToStr(tuple2);
 
     //std::list<int>  testList = { 172, 16, 147, 35};
     //auto resList = MyIP::ToStr(testList);
 
     //std::vector<int>  testVect = { 172, 16, 147, 35 };
     //auto resVect = MyIP::ToStr(testVect);

    return 0;
}
//-----------------------------------------------------------------------------

