#include <gtest/gtest.h> // googletest header file
#include "../ip_filter/ip_filter.h"
#include "../md5/md5.h"
#include "../bin_pow/bin_pow.h"

TEST(gtest_test, TestBinPow)
{
    ASSERT_NO_THROW(
        bin_pow::BinPowTest()
    );
}


TEST(gtest_test, TestIpFilter)
{
    auto res = ip_filter::SortAndFilterIPv4ForOtus("ip_filter-12995-758870.tsv");
    auto md5Sum = md5(res);
    ASSERT_STRCASEEQ(md5Sum.c_str(),  "24e7a7b2270daee89c64d3ca5fb3da1a");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}