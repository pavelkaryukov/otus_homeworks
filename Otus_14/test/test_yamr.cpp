#include <gtest/gtest.h> // googletest header file
#include "prefix_finder/prefix_finder.h"

TEST(test_yamr, test_map_reduce) {
    using hash_t = std::string;
    using hashFactory_t = boost::factory<std::unique_ptr<HasherString>>;
    MapReduce<hash_t> mapReducer{ hashFactory_t(), 8,  6, ReduceFunc<hash_t> };
    const std::size_t uniqueHashs = mapReducer.Process({"test.csv"}, 16); //20876
    //в справочнике ip адресов уникальность дает 16 символов, число уникальных записей = 20876
    ASSERT_EQ(20876, uniqueHashs);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}