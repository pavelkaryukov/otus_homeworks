#include "otus.h"
#include <gtest/gtest.h> // googletest header file

TEST(gtest_test_otus3, TestFactorial)
{
    ASSERT_NO_THROW(otus::FactorialTest());
}


TEST(gtest_test_otus3, TestAllocator)
{
    otus::StandardMap mapStandartAllocator;
    otus::CustomMap mapCustomAllocator;
    otus::FillMap(mapStandartAllocator);
    ASSERT_NO_THROW(otus::FillMap(mapCustomAllocator));
    ASSERT_EQ(mapCustomAllocator.size(), mapStandartAllocator.size());
    const int mapSize = mapStandartAllocator.size();
    for (auto i = 0; i < mapSize; ++i) {
        ASSERT_EQ(mapCustomAllocator[i], mapStandartAllocator[i]);
    }
}

TEST(gtest_test_otus3, TestMyContainer)
{
    otus::StandardMyList myListStandartAllocator;
    otus::CustomMyList   myListCustomAllocator;
    ASSERT_NO_THROW(otus::FillMyList(myListStandartAllocator));
    ASSERT_NO_THROW(otus::FillMyList(myListCustomAllocator  )  );
    ASSERT_EQ(myListStandartAllocator.size(), 10);
    ASSERT_EQ(myListCustomAllocator.size(), 10);
    const std::size_t listSize = myListCustomAllocator.size();
    auto standardIter = myListStandartAllocator.begin();
    auto customIter   = myListCustomAllocator.begin();

    for (auto i = 0; i < listSize; ++i) {
        ASSERT_EQ(*standardIter, i);
        ASSERT_EQ(*customIter, i);
        ++standardIter;
        ++customIter  ;
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}