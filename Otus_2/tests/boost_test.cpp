#define BOOST_TEST_MODULE test_version
#include <boost/test/unit_test.hpp>
#include "../ip_filter/ip_filter.h"
#include "../md5/md5.h"
#include "../bin_pow/bin_pow.h"
BOOST_AUTO_TEST_SUITE(boost_test_version)

BOOST_AUTO_TEST_CASE(boost_test_valid_version)
{
    BOOST_CHECK_NO_THROW(bin_pow::BinPowTest());
    auto res = ip_filter::SortAndFilterIPv4ForOtus("ip_filter-12995-758870.tsv");
    auto md5Sum = md5(res);
    BOOST_CHECK(md5Sum == "24e7a7b2270daee89c64d3ca5fb3da1a");
}
BOOST_AUTO_TEST_SUITE_END()
