#include <gtest/gtest.h> // googletest header file
#include "ip_to_str.h"
#include <array>
#include <list>
#include <vector>
//-----------------------------------------------------------------------------
TEST(gtest_print_ip,  PrintTuple)//TODO::Переделать тест
{
    std::tuple<int, int, int, int>   tuple1 = { 1, 12, 25, 67 };
    std::tuple<int, short, std::uint64_t> tuple2 = { 1, 12, 25};

    auto res11 = MyIP::ToStr<int, int, int, int >(tuple1, MyIP::ByteOrder::BigEndian);
    auto res12 = MyIP::ToStr<int, int, int, int>(tuple1, MyIP::ByteOrder::LittleEndian);
    auto res21 = MyIP::ToStr<int, short, std::uint64_t >(tuple2);
    auto res22 = MyIP::ToStr<int, short, std::uint64_t >(tuple2);

    ASSERT_EQ(res11.ErrorCode, MyIP::ErrorCode::Success);
    ASSERT_EQ(res12.ErrorCode, MyIP::ErrorCode::Success);

    ASSERT_NE(res21.ErrorCode, MyIP::ErrorCode::Success);
    ASSERT_NE(res22.ErrorCode, MyIP::ErrorCode::Success);

    ASSERT_EQ(res11.Result, "1.12.25.67");
    ASSERT_EQ(res12.Result, "67.25.12.1");

    ASSERT_TRUE(res21.Result.empty());
    ASSERT_TRUE(res22.Result.empty());
}
//-----------------------------------------------------------------------------
TEST(gtest_print_ip, PrintContainer)
{
    std::array <int, 4> array1 = { 1, 12, 25, 67 };
    std::vector<int>    vect1  = { 1, 12, 25, 67 };
    std::list  <int>    list1  = { 1, 12, 25, 67 };

    auto resArray11 = MyIP::ToStr<std::array<int, 4>>(array1, MyIP::ByteOrder::BigEndian);
    auto resArray12 = MyIP::ToStr<std::array<int, 4>>(array1, MyIP::ByteOrder::LittleEndian);
    auto resVect11  = MyIP::ToStr<std::vector<int>>  (vect1, MyIP::ByteOrder::BigEndian);
    auto resVect12  = MyIP::ToStr<std::vector<int>>  (vect1, MyIP::ByteOrder::LittleEndian);
    auto resList11  = MyIP::ToStr<std::list<int>>    (list1, MyIP::ByteOrder::BigEndian);
    auto resList12  = MyIP::ToStr<std::list<int>>    (list1, MyIP::ByteOrder::LittleEndian);


    
    ASSERT_EQ(resArray11.ErrorCode, MyIP::ErrorCode::Success);
    ASSERT_EQ(resArray12.ErrorCode, MyIP::ErrorCode::Success);

    ASSERT_EQ(resVect11 .ErrorCode, MyIP::ErrorCode::Success);
    ASSERT_EQ(resVect12 .ErrorCode, MyIP::ErrorCode::Success);

    ASSERT_EQ(resList11 .ErrorCode, MyIP::ErrorCode::Success);
    ASSERT_EQ(resList12 .ErrorCode, MyIP::ErrorCode::Success);

    ASSERT_EQ(resArray11.Result, "1.12.25.67");
    ASSERT_EQ(resArray12.Result, "67.25.12.1");

    ASSERT_EQ(resVect11.Result, "1.12.25.67");
    ASSERT_EQ(resVect12.Result, "67.25.12.1");

    ASSERT_EQ(resList11.Result, "1.12.25.67");
    ASSERT_EQ(resList12.Result, "67.25.12.1");
}
//-----------------------------------------------------------------------------
TEST(gtest_print_ip, PrintIntegral)
{
    auto test1 = char(-1);
    auto test2 = short(0);
    auto test3 = int(2130706433);
    auto test4 = std::uint64_t(8875824491850138409);
    
    auto res1 = MyIP::ToStr<decltype(test1)>(test1);
    auto res2 = MyIP::ToStr<decltype(test2)>(test2);
    auto res3 = MyIP::ToStr<decltype(test3)>(test3);
    auto res4 = MyIP::ToStr<decltype(test4)>(test4);

    ASSERT_EQ(res1.ErrorCode, MyIP::ErrorCode::Success);
    ASSERT_EQ(res2.ErrorCode, MyIP::ErrorCode::Success);
    ASSERT_EQ(res3.ErrorCode, MyIP::ErrorCode::Success);
    ASSERT_EQ(res4.ErrorCode, MyIP::ErrorCode::Success);
    
    ASSERT_EQ(res1.Result, "255"                        );
    ASSERT_EQ(res2.Result, "0.0"                        );
    ASSERT_EQ(res3.Result, "127.0.0.1"                  );
    ASSERT_EQ(res4.Result, "123.45.67.89.101.112.131.41");
}
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}