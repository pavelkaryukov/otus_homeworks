#include <gtest/gtest.h> // googletest header file
#include "ip_to_str.h"
//-----------------------------------------------------------------------------
TEST(gtest_print_ip,  PrintTuple)
{
    std::tuple<int, int, int, int>   tuple1 = { 1, 12, 25, 67 };
    std::tuple<int, short, long long> tuple2 = { 1, 12, 25};

    auto res11 = MyIP::ToStr<int, int, int, int >(tuple1, MyIP::ByteOrder::BigEndian);
    auto res12 = MyIP::ToStr<int, int, int, int>(tuple1, MyIP::ByteOrder::LittleEndian);
    auto res21 = MyIP::ToStr<int, short, std::uint64_t >(tuple2);
    auto res22 = MyIP::ToStr<int, short, std::uint64_t >(tuple2);

    ASSERT_EQ(res11.second, MyIP::ErrorCode::Success);
    ASSERT_EQ(res12.second, MyIP::ErrorCode::Success);

    ASSERT_NE(res21.second, MyIP::ErrorCode::Success); 
    ASSERT_NE(res22.second, MyIP::ErrorCode::Success); 

    ASSERT_EQ(res11.first, "1.12.25.67");
    ASSERT_EQ(res12.first, "67.25.12.1");

    ASSERT_TRUE(res11.first.empty());
    ASSERT_TRUE(res12.first.empty());
}
//-----------------------------------------------------------------------------
// TEST(gtest_test_otus3, TestAllocator)
// {
//     otus::StandardMap mapStandartAllocator;
//     otus::CustomMap mapCustomAllocator;
//     otus::FillMap(mapStandartAllocator);
//     ASSERT_NO_THROW(otus::FillMap(mapCustomAllocator));
//     ASSERT_EQ(mapCustomAllocator.size(), mapStandartAllocator.size());
//     const int mapSize = mapStandartAllocator.size();
//     for (auto i = 0; i < mapSize; ++i) {
//         ASSERT_EQ(mapCustomAllocator[i], mapStandartAllocator[i]);
//     }
// }
// 
// TEST(gtest_test_otus3, TestMyContainer)
// {
//     otus::StandardMyList myListStandartAllocator;
//     otus::CustomMyList   myListCustomAllocator;
//     ASSERT_NO_THROW(otus::FillMyList(myListStandartAllocator));
//     ASSERT_NO_THROW(otus::FillMyList(myListCustomAllocator));
//     ASSERT_EQ(myListStandartAllocator.size(), 10);
//     ASSERT_EQ(myListCustomAllocator.size(), 10);
//     const std::size_t listSize = myListCustomAllocator.size();
//     auto standardIter = myListStandartAllocator.begin();
//     auto customIter = myListCustomAllocator.begin();
// 
//     for (auto i = 0; i < listSize; ++i) {
//         ASSERT_EQ(*standardIter, i);
//         ASSERT_EQ(*customIter, i);
//         ++standardIter;
//         ++customIter;
//     }
// }


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}