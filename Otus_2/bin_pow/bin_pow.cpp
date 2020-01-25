#include "bin_pow.h"
#include <type_traits>
#include <assert.h>
//-----------------------------------------------------------------------------
void bin_pow::BinPowTest()
{
    //const auto test = GetMinBinPow(1);
    static_assert(bin_pow::Step(5, 2));
    static_assert(bin_pow::BinExp(4));
    static_assert(bin_pow::GetMinBinPow(4));
    static_assert(bin_pow::GetMinBinPow(0) == 0);
    static_assert(bin_pow::GetMinBinPow(1) == 0);
    static_assert(bin_pow::GetMinBinPow(2) == 1);
    static_assert(bin_pow::GetMinBinPow(4) == 2);
    static_assert(bin_pow::GetMinBinPow(7) == 3);
    static_assert(bin_pow::GetMinBinPow(8) == 3);
    static_assert(bin_pow::GetMinBinPow(9) == 4);
    static_assert(bin_pow::GetMinBinPow(1023) == 10);
    static_assert(bin_pow::GetMinBinPow(1024) == 10);
    static_assert(bin_pow::GetMinBinPow(1025) == 11);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 - 33) == 20);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024) == 20);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 + 33) == 21);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 * 1024 - 127) == 30);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 * 1024) == 30);
    static_assert(bin_pow::GetMinBinPow(1024 * 1024 * 1024 + 127) == 31);
}
//-----------------------------------------------------------------------------
